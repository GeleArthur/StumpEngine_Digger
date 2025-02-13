cmake_minimum_required(VERSION 3.29..3.29)

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
endif()


if(WIN32)
  set(TARGET_PARAM WIN32)
else()
  set(TARGET_PARAM )
endif()

add_executable(${PROJECT_NAME} ${TARGET_PARAM}
  src/main.cpp
  "src/GameObject.cpp" "src/GameObject.h" "src/Minigin.h" "src/Minigin.cpp" "src/component.h" "src/component.cpp")

if(MSVC)
    # VLD reports memory leaks
    #target_compile_options(${PROJECT_NAME} PUBLIC /fsanitize=address)
endif()


target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)


include(FetchContent)
# add glm
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG release-1.0.2
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(glm)

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
  GIT_TAG 3d7b6efedd0d2c9cfc6ee0a18906550d6c98d07a
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
FetchContent_MakeAvailable(SDL3_mixer)


target_link_libraries(${PROJECT_NAME} PUBLIC 
    SDL3_ttf::SDL3_ttf   
    SDL3_mixer::SDL3_mixer  
    SDL3_image::SDL3_image	
    SDL3::SDL3              
)

if(WIN32)
  find_package(VLD CONFIG)
  target_include_directories(${PROJECT_NAME} PRIVATE ${VLD_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} PUBLIC ${VLD_LIBRARY})
endif()


# target_compile_definitions(${PROJECT_NAME} PUBLIC SDL_MAIN_USE_CALLBACKS)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)

if(EMSCRIPTING)
  # TODO: Import all of the data folder
  # target_link_libraries(${PROJECT_NAME} PRIVATE 
  #   "--preload-file \"${CMAKE_CURRENT_LIST_DIR}/src/Inter-VariableFont.ttf@/\""
  #   "--preload-file \"${CMAKE_CURRENT_LIST_DIR}/src/the_entertainer.ogg@/\""
  # )
endif()
