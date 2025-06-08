cmake_minimum_required(VERSION 3.28)

project(Digger)

add_subdirectory(StumpEngine)
add_subdirectory(Digger)

# Subcheck bypass
target_compile_features(Digger PRIVATE cxx_std_23)
target_compile_features(StumpEngine PRIVATE cxx_std_23)

