cmake_minimum_required(VERSION 3.16)
project(TSnake3SDL VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL3
find_package(SDL3 QUIET)

if(NOT SDL3_FOUND)
    include(FetchContent)
    message(STATUS "SDL3 not found. Fetching from GitHub...")
    
    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG main
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
    )
    
    set(SDL_SHARED ON CACHE BOOL "Build SDL3 as shared library" FORCE)
    set(SDL_STATIC OFF CACHE BOOL "Build SDL3 as static library" FORCE)
    set(SDL_TEST OFF CACHE BOOL "Build SDL3 test programs" FORCE)
    
    # Allow building without X11/Wayland in headless environments
    set(SDL_UNIX_CONSOLE_BUILD ON CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(SDL3)
endif()

# Source files
set(SOURCES
    src/main.cpp
    src/game.cpp
)

set(HEADERS
    src/game.h
)

# Create executable
add_executable(tsnake3 ${SOURCES} ${HEADERS})

# Link SDL3
if(TARGET SDL3::SDL3)
    target_link_libraries(tsnake3 PRIVATE SDL3::SDL3)
else()
    target_link_libraries(tsnake3 PRIVATE SDL3)
endif()

# Include directories
target_include_directories(tsnake3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Set output directory
set_target_properties(tsnake3 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy assets to build directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/assets)
