#pragma once
#include <glm.hpp>

class Command
{
public:
    virtual ~Command() = default;
    virtual void execute() = 0;

    Command(const Command& other) = delete;
    Command(Command&& other) = delete;
    Command& operator=(const Command& other) = delete;
    Command& operator=(Command&& other) = delete;
};

class CommandAxis
{
public:
    virtual ~CommandAxis() = default;
    virtual void execute(float axis) = 0;

    CommandAxis(const CommandAxis& other) = delete;
    CommandAxis(CommandAxis&& other) = delete;
    CommandAxis& operator=(const CommandAxis& other) = delete;
    CommandAxis& operator=(CommandAxis&& other) = delete;
};

class CommandAxis2D
{
public:
    virtual ~CommandAxis2D() = default;
    virtual void execute(glm::vec2 axis) = 0;

    CommandAxis2D(const CommandAxis2D& other) = delete;
    CommandAxis2D(CommandAxis2D&& other) = delete;
    CommandAxis2D& operator=(const CommandAxis2D& other) = delete;
    CommandAxis2D& operator=(CommandAxis2D&& other) = delete;
};
