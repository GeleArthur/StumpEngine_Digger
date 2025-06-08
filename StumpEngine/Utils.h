#pragma once

#define NO_MOVE(class)              \
    class(class && other) = delete; \
    class& operator=(class&& other) = delete;

#define NO_COPY(class)                  \
    class(const class& other) = delete; \
    class& operator=(const class& other) = delete;\
