cmake_minimum_required(VERSION 3.28)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# prevent installing to system directories. 
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE INTERNAL "")

if(EMSCRIPTEN)
    set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "")    # Disable shared builds on platforms where it does not make sense to use them
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()


if(WIN32)
    set(TARGET_PARAM WIN32)
else()
    set(TARGET_PARAM
            Components/BackGroundDrawer.cpp
            Components/BackGroundDrawer.h)
endif()

file(GLOB_RECURSE source_files CONFIGURE_DEPENDS "*.cpp" "*.h")

add_executable(${PROJECT_NAME} ${TARGET_PARAM} ${source_files})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_link_libraries(${PROJECT_NAME} PUBLIC StumpEngine)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${PROJECT_NAME}> $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
        COMMAND_EXPAND_LISTS
)

if(MSVC)
    # VLD reports memory leaks
    #target_compile_options(${PROJECT_NAME} PUBLIC /fsanitize=address)
endif()
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)


if(WIN32)
    find_package(VLD CONFIG)
    target_include_directories(${PROJECT_NAME} PRIVATE ${VLD_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${VLD_LIBRARY})
    set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endif()


set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

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
else()
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_directory "${CMAKE_SOURCE_DIR}/data" "$<TARGET_FILE_DIR:${PROJECT_NAME}>/data"
    )
endif()

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/.gitignore *)