#include "EngineTime.h"

namespace stump
{
    EngineTime& EngineTime::instance()
    {
        static EngineTime instance;
        return instance;
    }
} // namespace stump