cmake_minimum_required(VERSION 3.15)

project(VorteX
    VERSION 0.9
    LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

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

target_link_libraries(VorteX SDL2::Main SDL2::Image SDL2::Mixer)

set_target_properties(VorteX PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF)

target_compile_options(VorteX PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -Werror>)
