cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER               gcc)
set(CMAKE_CXX_COMPILER             g++)
set(CMAKE_ASM_COMPILER             gcc)

# Set the project name
project(zb-gw-unify)

add_subdirectory(cli)
add_subdirectory(app)

# Add an executable target
add_executable(zb-gw-unify main.c)

target_link_libraries(zb-gw-unify
    cli
    app)

# Include directories
target_include_directories(zb-gw-unify PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/common)