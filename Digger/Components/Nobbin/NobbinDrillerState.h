#pragma once
#include "INobbinState.h"

class NobbinDrillerState final : public INobbinState
{
public:
    virtual std::unique_ptr<INobbinState> update() override;
};
