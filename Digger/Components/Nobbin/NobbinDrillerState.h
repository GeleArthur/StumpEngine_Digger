#pragma once
#include "INobelState.h"

class NobbinDrillerState : public INobelState
{
public:
    virtual std::unique_ptr<INobelState> update(Nobbin& nobbin) override;
};
