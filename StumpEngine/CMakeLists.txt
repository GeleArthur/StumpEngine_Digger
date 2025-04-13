cmake_minimum_required(VERSION 3.28)


file(GLOB_RECURSE source_files CONFIGURE_DEPENDS "*.cpp" "*.h")

# Remove this 
if(WIN32)
    get_filename_component(full_path ${CMAKE_CURRENT_SOURCE_DIR}/Input/GamepadHandlerSDL.cpp ABSOLUTE)
    list(REMOVE_ITEM source_files ${full_path})
    get_filename_component(full_path2 ${CMAKE_CURRENT_SOURCE_DIR}/Sleep/HighResolutionSleepGlobal.cpp ABSOLUTE)
    list(REMOVE_ITEM source_files ${full_path2})
else()
    get_filename_component(full_path ${CMAKE_CURRENT_SOURCE_DIR}/Input/GamepadHandlerXInput.cpp ABSOLUTE)
    list(REMOVE_ITEM source_files ${full_path})
    get_filename_component(full_path2 ${CMAKE_CURRENT_SOURCE_DIR}/Sleep/HighResolutionSleepWindows.cpp ABSOLUTE)
    list(REMOVE_ITEM source_files ${full_path2})
endif()

add_library(StumpEngine STATIC ${source_files})
target_compile_features(StumpEngine PRIVATE cxx_std_20)

file(GLOB_RECURSE header_files CONFIGURE_DEPENDS "*.h")
target_include_directories(StumpEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(StumpEngine PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

# Import libarys

include(FetchContent)
FetchContent_Declare(
        glm
        URL https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip
)
FetchContent_MakeAvailable(glm)
target_include_directories(StumpEngine PUBLIC ${glm_SOURCE_DIR})

FetchContent_Declare(
        imgui
        URL https://github.com/ocornut/imgui/archive/refs/tags/v1.91.8.zip
)
FetchContent_MakeAvailable(imgui)

target_include_directories(StumpEngine PUBLIC ${imgui_SOURCE_DIR})
target_sources(StumpEngine PUBLIC
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
target_include_directories(StumpEngine PUBLIC ${implot_SOURCE_DIR})
target_sources(StumpEngine PUBLIC
        ${implot_SOURCE_DIR}/implot.cpp
        ${implot_SOURCE_DIR}/implot_items.cpp
        ${implot_SOURCE_DIR}/implot_demo.cpp
)


if(WIN32) # subcheck support 
    include(FetchContent)
    FetchContent_Declare(
            SDL3
            URL https://github.com/libsdl-org/SDL/releases/download/release-3.2.4/SDL3-devel-3.2.4-VC.zip
            DOWNLOAD_NO_PROGRESS ON
    )
    FetchContent_MakeAvailable(sdl3)
    add_library(SDL3::SDL3 SHARED IMPORTED)
    set_target_properties(SDL3::SDL3 PROPERTIES
            IMPORTED_LOCATION "${sdl3_SOURCE_DIR}/lib/x64/SDL3.dll"
            IMPORTED_IMPLIB "${sdl3_SOURCE_DIR}/lib/x64/SDL3.lib"
            INTERFACE_INCLUDE_DIRECTORIES ${sdl3_SOURCE_DIR}/include
    )
    target_link_libraries(StumpEngine PUBLIC SDL3::SDL3)

    FetchContent_Declare(
            SDL3_image
            URL https://github.com/libsdl-org/SDL_image/releases/download/release-3.2.0/SDL3_image-devel-3.2.0-VC.zip
            DOWNLOAD_NO_PROGRESS ON
    )
    FetchContent_MakeAvailable(SDL3_image)
    add_library(SDL3_image::SDL3_image SHARED IMPORTED)
    set_target_properties(SDL3_image::SDL3_image PROPERTIES
            IMPORTED_LOCATION "${sdl3_image_SOURCE_DIR}/lib/x64/SDL3_image.dll"
            IMPORTED_IMPLIB "${sdl3_image_SOURCE_DIR}/lib/x64/SDL3_image.lib"
            INTERFACE_INCLUDE_DIRECTORIES ${sdl3_image_SOURCE_DIR}/include
    )
    target_link_libraries(StumpEngine PUBLIC SDL3_image::SDL3_image)

    FetchContent_Declare(
            SDL3_ttf
            URL https://github.com/libsdl-org/SDL_ttf/releases/download/preview-3.1.0/SDL3_ttf-devel-3.1.0-VC.zip
            DOWNLOAD_NO_PROGRESS ON
    )
    FetchContent_MakeAvailable(sdl3_ttf)
    add_library(SDL3_ttf::SDL3_ttf SHARED IMPORTED)
    set_target_properties(SDL3_ttf::SDL3_ttf PROPERTIES
            IMPORTED_LOCATION "${sdl3_ttf_SOURCE_DIR}/lib/x64/SDL3_ttf.dll"
            IMPORTED_IMPLIB "${sdl3_ttf_SOURCE_DIR}/lib/x64/SDL3_ttf.lib"
            INTERFACE_INCLUDE_DIRECTORIES ${sdl3_ttf_SOURCE_DIR}/include
    )
    target_link_libraries(StumpEngine PUBLIC SDL3_ttf::SDL3_ttf)

    # Because there is no official release yet I have a local copy 
    set(sdl3_mixer_SOURCE_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/SDL3_mixer-3.0.0-windows-VC-x64")
    add_library(SDL3_mixer::SDL3_mixer SHARED IMPORTED)
    set_target_properties(SDL3_mixer::SDL3_mixer PROPERTIES
            IMPORTED_LOCATION "${sdl3_mixer_SOURCE_DIR}/bin/SDL3_mixer.dll"
            IMPORTED_IMPLIB "${sdl3_mixer_SOURCE_DIR}/lib/SDL3_mixer.lib"
            INTERFACE_INCLUDE_DIRECTORIES ${sdl3_mixer_SOURCE_DIR}/include
    )
    target_link_libraries(StumpEngine PUBLIC SDL3_mixer::SDL3_mixer)

else()
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
            GIT_TAG 6509f9f2117513bd8d6677c4370194be932b1fe8
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(SDL3_mixer)

    target_link_libraries(StumpEngine PUBLIC
            SDL3_ttf::SDL3_ttf
            SDL3_mixer::SDL3_mixer
            SDL3_image::SDL3_image
            SDL3::SDL3
    )
endif()

# Import steam
if(NOT EMSCRIPTING)
    #    set(STEAM_SDK ${CMAKE_SOURCE_DIR}/ThirdParty/SteamSDK)
    #    if(WIN32)
    #        add_library(SteamSDK::SteamSDK SHARED IMPORTED)
    #        set_target_properties(SteamSDK::SteamSDK PROPERTIES
    #                IMPORTED_LOCATION "${STEAM_SDK}/redistributable_bin/win64/steam_api64.dll"
    #                IMPORTED_IMPLIB "${STEAM_SDK}/redistributable_bin/win64/steam_api64.lib"
    #                INTERFACE_INCLUDE_DIRECTORIES ${STEAM_SDK}/public/steam
    #        )
    #        target_link_libraries(StumpEngine PUBLIC SteamSDK::SteamSDK)
    #        target_compile_definitions(StumpEngine PUBLIC _CRT_SECURE_NO_WARNINGS)
    #    elseif(UNIX)
    #        add_library(SteamSDK::SteamSDK SHARED IMPORTED)
    #        set_target_properties(SteamSDK::SteamSDK PROPERTIES
    #                IMPORTED_IMPLIB "${STEAM_SDK}/redistributable_bin/linux64/libsteam_api.so"
    #                IMPORTED_LOCATION "${STEAM_SDK}/redistributable_bin/linux64/libsteam_api.so"
    #                INTERFACE_INCLUDE_DIRECTORIES ${STEAM_SDK}/public/steam
    #        )
    #        target_link_libraries(StumpEngine PUBLIC SteamSDK::SteamSDK)
    #        target_compile_definitions(StumpEngine PUBLIC _CRT_SECURE_NO_WARNINGS)
    #    endif()

endif()