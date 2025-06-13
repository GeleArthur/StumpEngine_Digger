#pragma once

#include <memory>

class Nobbin;
class INobbinState
{
public:
    INobbinState() = default;
    virtual ~INobbinState() = default;
    INobbinState(const INobbinState& other) = delete;
    INobbinState(INobbinState&& other) = delete;
    INobbinState& operator=(const INobbinState& other) = delete;
    INobbinState& operator=(INobbinState&& other) = delete;

    virtual std::unique_ptr<INobbinState> update() = 0;
    virtual bool                          can_mine() = 0;
};
