#include "HighResolutionSleep.h"

#include <chrono>
#include <math.h>
#include <thread>

void stump::high_resolution_sleep::init_precise_sleep()
{
}

void stump::high_resolution_sleep::precise_sleep(double seconds)
{
    std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
}
