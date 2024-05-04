cmake_minimum_required(VERSION 3.15)

project(VorteX
    VERSION 0.9
    LANGUAGES CXX)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

add_executable(
    VorteX
    "Project X/main.cpp"
    "Project X/coreDef.cpp"
    "Project X/Bullets.cpp"
    "Project X/GruntShip.cpp"
    "Project X/LWindow.cpp"
    "Project X/PlayerShip.cpp"
    "Project X/LTexture.cpp"
    "Project X/Ship.cpp")

target_link_libraries(VorteX SDL2 SDL2_image::SDL2_image SDL2_mixer fmt spdlog)

set_target_properties(VorteX PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF)

target_compile_options(VorteX PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -Werror>)
