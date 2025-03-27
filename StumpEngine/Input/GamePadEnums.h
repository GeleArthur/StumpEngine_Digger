#pragma once

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
