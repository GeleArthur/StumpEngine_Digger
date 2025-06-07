#pragma once

namespace stump
{
    namespace high_resolution_sleep
    {
        void init_precise_sleep();

        void precise_sleep(double seconds);
    } // namespace high_resolution_sleep
} // namespace stump