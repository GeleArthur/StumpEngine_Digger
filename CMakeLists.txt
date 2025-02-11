cmake_minimum_required(VERSION 3.29)

project(MiniginSDL3)





if(NOT EMSCRIPTEN)
    include(FetchContent)

    FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.4
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(SDL3)
endif()


