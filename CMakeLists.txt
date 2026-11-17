cmake_minimum_required(VERSION 3.13)

project(probleme_des_dictateurs)

add_executable(main
    src/main.cpp
    src/Frame3D.cpp
)

target_compile_features(main PRIVATE cxx_std_11)

if (MSVC)
    target_compile_options(main PRIVATE /W3)
else()
    target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors)
endif()