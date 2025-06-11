#pragma once
#include "Nobbin.h"

#include <memory>

class INobelState
{
public:
    virtual ~INobelState() = default;
    INobelState(const INobelState& other) = delete;
    INobelState(INobelState&& other) = delete;
    INobelState& operator=(const INobelState& other) = delete;
    INobelState& operator=(INobelState&& other) = delete;

    virtual std::unique_ptr<INobelState> update(Nobbin& nobbin) = 0;
};
