cmake_minimum_required(VERSION 3.28)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# prevent installing to system directories. 
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE INTERNAL "")

project(miniginSDL3)

if (EMSCRIPTEN)
    set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")    # Disable shared builds on platforms where it does not make sense to use them
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif ()


if (WIN32)
    set(TARGET_PARAM WIN32)
else ()
    set(TARGET_PARAM)
endif ()

# I gave in
file(GLOB_RECURSE source_files CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")

if (WIN32)
    list(REMOVE_ITEM source_files "src/GamepadHandlerSDL.cpp")
else ()
    list(REMOVE_ITEM source_files "src/GamepadHandlerXInput.cpp")
endif ()


add_executable(${PROJECT_NAME} ${TARGET_PARAM}
        ${source_files}
)

if (MSVC)
    # VLD reports memory leaks
    #target_compile_options(${PROJECT_NAME} PUBLIC /fsanitize=address)
endif ()


target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

include(FetchContent)

FetchContent_Declare(
        glm
        URL https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip
)
FetchContent_MakeAvailable(glm)
target_include_directories(${PROJECT_NAME} PRIVATE ${glm_SOURCE_DIR})

FetchContent_Declare(
        imgui
        URL https://github.com/ocornut/imgui/archive/refs/tags/v1.91.8.zip
)
FetchContent_MakeAvailable(imgui)
target_include_directories(${PROJECT_NAME} PRIVATE ${imgui_SOURCE_DIR})
target_sources(${PROJECT_NAME} PRIVATE
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer3.h
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.h
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
)

FetchContent_Declare(
        implot
        URL https://github.com/epezent/implot/archive/refs/tags/v0.16.zip
)
FetchContent_MakeAvailable(implot)
target_include_directories(${PROJECT_NAME} PRIVATE ${implot_SOURCE_DIR})
target_sources(${PROJECT_NAME} PRIVATE
        ${implot_SOURCE_DIR}/implot.cpp
        ${implot_SOURCE_DIR}/implot_items.cpp
        ${implot_SOURCE_DIR}/implot_demo.cpp
)


if (WIN32) # subcheck support     
    FetchContent_Declare(
            SDL3
            URL https://github.com/libsdl-org/SDL/releases/download/release-3.2.4/SDL3-devel-3.2.4-VC.zip
            DOWNLOAD_NO_PROGRESS ON
    )
    FetchContent_MakeAvailable(SDL3)

    target_include_directories(${PROJECT_NAME} PRIVATE ${sdl3_SOURCE_DIR}/include)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${sdl3_SOURCE_DIR}/lib/x64/SDL3.lib)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy "${sdl3_SOURCE_DIR}/lib/x64/SDL3.dll" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )

    FetchContent_Declare(
            SDL3_image
            URL https://github.com/libsdl-org/SDL_image/releases/download/release-3.2.0/SDL3_image-devel-3.2.0-VC.zip
            DOWNLOAD_NO_PROGRESS ON
    )
    FetchContent_MakeAvailable(SDL3_image)
    target_include_directories(${PROJECT_NAME} PRIVATE ${sdl3_image_SOURCE_DIR}/include)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${sdl3_image_SOURCE_DIR}/lib/x64/SDL3_image.lib)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy "${sdl3_image_SOURCE_DIR}/lib/x64/SDL3_image.dll" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )

    FetchContent_Declare(
            SDL3_ttf
            URL https://github.com/libsdl-org/SDL_ttf/releases/download/preview-3.1.0/SDL3_ttf-devel-3.1.0-VC.zip
            DOWNLOAD_NO_PROGRESS ON
    )
    FetchContent_MakeAvailable(SDL3_ttf)
    target_include_directories(${PROJECT_NAME} PRIVATE ${sdl3_ttf_SOURCE_DIR}/include)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${sdl3_ttf_SOURCE_DIR}/lib/x64/SDL3_ttf.lib)

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy "${sdl3_ttf_SOURCE_DIR}/lib/x64/SDL3_ttf.dll" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )

else ()
    # add glm

    FetchContent_Declare(
            SDL3
            GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
            GIT_TAG release-3.2.4
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(SDL3)

    # SDL Image
    set(SDLIMAGE_VENDORED ON)
    set(SDLIMAGE_AVIF OFF)
    set(SDLIMAGE_BMP OFF)
    set(SDLIMAGE_JPEG OFF)
    set(SDLIMAGE_WEBP OFF)
    set(SDLIMAGE_TIF_SHARED OFF)
    set(SDLIMAGE_TIF OFF)
    FetchContent_Declare(
            SDL3_image
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
            GIT_TAG release-3.2.0
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(SDL3_image)

    # SDL TTF
    set(SDLTTF_VENDORED ON)
    set(PLUTOSVG_BUILD_EXAMPLES OFF)
    FetchContent_Declare(
            SDL3_ttf
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
            GIT_TAG 07e4d1241817f2c0f81749183fac5ec82d7bbd72
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(SDL3_ttf)

    # SDL MIXER
    set(SDLMIXER_MIDI_NATIVE OFF)     # disable formats we don't use to make the build faster and smaller. Also some of these don't work on all platforms so you'll need to do some experimentation.
    set(SDLMIXER_GME OFF)
    set(SDLMIXER_WAVPACK OFF)
    set(SDLMIXER_MOD OFF)
    set(SDLMIXER_OPUS OFF)
    set(SDLMIXER_VENDORED ON)   # tell SDL_mixer to build its own dependencies
    FetchContent_Declare(
            SDL3_mixer
            GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
            GIT_TAG ebdd9cc0fe43352e33ec234f4720fd7d54a31d13
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    # Crashes visual studio with clang.
    #FetchContent_MakeAvailable(SDL3_mixer)

    target_link_libraries(${PROJECT_NAME} PUBLIC
            SDL3_ttf::SDL3_ttf
            #            SDL3_mixer::SDL3_mixer
            SDL3_image::SDL3_image
            SDL3::SDL3
    )
endif ()


if (WIN32)
    find_package(VLD CONFIG)
    target_include_directories(${PROJECT_NAME} PRIVATE ${VLD_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${VLD_LIBRARY})
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endif ()


# target_compile_definitions(${PROJECT_NAME} PUBLIC SDL_MAIN_USE_CALLBACKS)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

if (EMSCRIPTING)
    # TODO: Import all of the data folder
    # target_link_libraries(${PROJECT_NAME} PRIVATE 
    #   "--preload-file \"${CMAKE_CURRENT_LIST_DIR}/src/Inter-VariableFont.ttf@/\""
    #   "--preload-file \"${CMAKE_CURRENT_LIST_DIR}/src/the_entertainer.ogg@/\""
    # )
else ()
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/data" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/data"
    )
endif ()

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/.gitignore *)