// https://github.com/blat-blatnik/Snippets/blob/main/precise_sleep.c
#include "HighResolutionSleep.h"

#include <Windows.h>
#pragma comment(lib, "Winmm.lib") // timeGetDevCaps, timeBeginPeriod
#include <stdio.h>

HANDLE Timer;
int SchedulerPeriodMs;
INT64 QpcPerSecond;

void high_resolution_sleep::init_precise_sleep()
{
    Timer = CreateWaitableTimerExW(NULL, NULL, CREATE_WAITABLE_TIMER_HIGH_RESOLUTION, TIMER_ALL_ACCESS);
    TIMECAPS caps;
    timeGetDevCaps(&caps, sizeof caps);
    timeBeginPeriod(caps.wPeriodMin);
    SchedulerPeriodMs = (int)caps.wPeriodMin;
    LARGE_INTEGER qpf;
    QueryPerformanceFrequency(&qpf);
    QpcPerSecond = qpf.QuadPart;
}

void high_resolution_sleep::precise_sleep(double seconds)
{
    LARGE_INTEGER qpc;
    QueryPerformanceCounter(&qpc);
    INT64 targetQpc = (INT64)(qpc.QuadPart + seconds * QpcPerSecond);

    if (Timer) // Try using a high resolution timer first.
    {
        const double TOLERANCE = 0.001'02;
        INT64 maxTicks = (INT64)SchedulerPeriodMs * 9'500;
        for (;;) // Break sleep up into parts that are lower than scheduler period.
        {
            double remainingSeconds = (targetQpc - qpc.QuadPart) / (double)QpcPerSecond;
            INT64 sleepTicks = (INT64)((remainingSeconds - TOLERANCE) * 10'000'000);
            if (sleepTicks <= 0)
                break;

            LARGE_INTEGER due;
            due.QuadPart = -(sleepTicks > maxTicks ? maxTicks : sleepTicks);
            SetWaitableTimerEx(Timer, &due, 0, NULL, NULL, NULL, 0);
            WaitForSingleObject(Timer, INFINITE);
            QueryPerformanceCounter(&qpc);
        }
    }
    else // Fallback to Sleep.
    {
        const double TOLERANCE = 0.000'02;
        double sleepMs = (seconds - TOLERANCE) * 1000 - SchedulerPeriodMs; // Sleep for 1 scheduler period less than requested.
        int sleepSlices = (int)(sleepMs / SchedulerPeriodMs);
        if (sleepSlices > 0)
            Sleep((DWORD)sleepSlices * SchedulerPeriodMs);
        QueryPerformanceCounter(&qpc);
    }

    while (qpc.QuadPart < targetQpc) // Spin for any remaining time.
    {
        YieldProcessor();
        QueryPerformanceCounter(&qpc);
    }
}
