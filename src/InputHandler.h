#pragma once

#include <iostream>
#include <vector>

#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_scancode.h>

#include "Command.h"

class CommandAxis2D;
class CommandAxis;
class Command;

enum class input_pressed_type
{
    pressed_this_frame,
    held_down,
    let_go_this_frame
};

enum class gamepad_axis_type
{
    axis_left_trigger,
    axis_right_trigger,
};

enum class gamepad_axis_2d_type
{
    axis_left_stick,
    axis_right_stick,
};

struct KeyboardInputSignature
{
    SDL_Scancode key_code;
    input_pressed_type input_type;
};

struct GamepadButtonSignature
{
    SDL_GamepadButton gamepad_button;
    input_pressed_type input_type;
};

struct GamepadAxisSignature
{
    gamepad_axis_type gamepad_axis;
    input_pressed_type input_type;
};

struct GamepadAxis2DSignature
{
    gamepad_axis_2d_type gamepad_axis2d;
    input_pressed_type input_type;
};

class InputHandler
{
public:
    void process_input();
    void bind_keyboard(const KeyboardInputSignature& keyboard_input_signature, std::unique_ptr<Command>&& command);
    void bind_gamepad_button(const GamepadButtonSignature& gamepad_button, std::unique_ptr<Command> command);
    void bind_gamepad_axis(const GamepadAxisSignature& gamepad_axis, std::unique_ptr<CommandAxis> command);
    void bind_gamepad_axis2d(const GamepadAxis2DSignature& gamepad_axis2d, std::unique_ptr<CommandAxis2D> command);

private:
    std::vector<std::tuple<KeyboardInputSignature, std::unique_ptr<Command>>> m_keyboard_bindings;
    std::vector<std::tuple<GamepadButtonSignature, std::unique_ptr<Command>>> m_gamepad_button_bindings;
    std::vector<std::tuple<GamepadAxisSignature, std::unique_ptr<CommandAxis>>> m_gamepad_axis_bindings;
    std::vector<std::tuple<GamepadAxis2DSignature, std::unique_ptr<CommandAxis2D>>> m_gamepad_axis2d_bindings;
};

