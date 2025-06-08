// https://github.com/blat-blatnik/Snippets/blob/main/precise_sleep.c
#include "HighResolutionSleep.h"

#include <Windows.h>
#pragma comment(lib, "Winmm.lib") // timeGetDevCaps, timeBeginPeriod
#include <stdio.h>

namespace
{
    HANDLE timer{};
    int    scheduler_period_ms{};
    INT64  qpc_per_second{};
} // namespace

void stump::high_resolution_sleep::init_precise_sleep()
{
    timer = CreateWaitableTimerExW(NULL, NULL, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_ALL_ACCESS);
    TIMECAPS caps;
    timeGetDevCaps(&caps, sizeof caps);
    timeBeginPeriod(caps.wPeriodMin);
    scheduler_period_ms = static_cast<int>(caps.wPeriodMin);
    LARGE_INTEGER qpf;
    QueryPerformanceFrequency(&qpf);
    qpc_per_second = qpf.QuadPart;
}

void stump::high_resolution_sleep::precise_sleep(double seconds)
{
    LARGE_INTEGER qpc;
    QueryPerformanceCounter(&qpc);
    const INT64 target_qpc = static_cast<INT64>(static_cast<double>(qpc.QuadPart) + seconds * static_cast<double>(qpc_per_second));

    if (timer) // Try using a high resolution timer first.
    {
        const INT64 max_ticks = static_cast<INT64>(scheduler_period_ms) * 9500;

        while (true) // Break sleep up into parts that are lower than scheduler period.
        {
            constexpr double tolerance = 0.00102;
            const double     remaining_seconds = static_cast<double>(target_qpc - qpc.QuadPart) / static_cast<double>(qpc_per_second);
            const INT64      sleep_ticks = static_cast<INT64>((remaining_seconds - tolerance) * 10'000'000);
            if (sleep_ticks <= 0)
                break;

            LARGE_INTEGER due;
            due.QuadPart = -(sleep_ticks > max_ticks ? max_ticks : sleep_ticks);
            SetWaitableTimerEx(timer, &due, 0, NULL, NULL, NULL, 0);
            WaitForSingleObject(timer, INFINITE);
            QueryPerformanceCounter(&qpc);
        }
    }
    else // Fallback to Sleep.
    {
        const double tolerance = 0.000'02;
        double       sleep_ms = (seconds - tolerance) * 1000 - scheduler_period_ms; // Sleep for 1 scheduler period less than requested.
        int          sleep_slices = (int)(sleep_ms / scheduler_period_ms);
        if (sleep_slices > 0)
            Sleep(static_cast<DWORD>(sleep_slices) * scheduler_period_ms);
        QueryPerformanceCounter(&qpc);
    }

    while (qpc.QuadPart < target_qpc) // Spin for any remaining time.
    {
        YieldProcessor();
        QueryPerformanceCounter(&qpc);
    }
}
