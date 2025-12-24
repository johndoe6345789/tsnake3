# T-Snake 3 - SDL3/C++ Port

This is a modern C++ port of the classic T-Snake 3 game (originally written in Visual Basic 6) using SDL3.

## About

T-Snake 3 is a classic snake game where you control a snake that grows as it eats food. Avoid hitting the walls or yourself!

**Original Version:** Copyright © 2005 T-RonX Modding  
**SDL3/C++ Port:** 2025

## Features

- Classic snake gameplay
- SDL3 graphics
- Keyboard controls (Arrow keys or WASD)
- Score tracking
- Collision detection

## Building

### Prerequisites

- CMake 3.16 or higher
- C++17 compatible compiler (GCC, Clang, or MSVC)
- SDL3 (automatically fetched if not found)

### Build Instructions

#### Linux/macOS

```bash
cd sdl3-cpp
mkdir build
cd build
cmake ..
cmake --build .
```

#### Windows

```bash
cd sdl3-cpp
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### Running the Game

After building, the executable will be in the `build/bin` directory:

#### Linux/macOS
```bash
./build/bin/tsnake3
```

#### Windows
```bash
.\build\bin\Release\tsnake3.exe
```

## Controls

- **Arrow Keys** or **WASD** - Move the snake
- **ESC** - Quit the game

## Game Rules

1. Use the arrow keys or WASD to control the snake's direction
2. Eat the red food to grow and increase your score
3. Avoid hitting the walls
4. Avoid hitting yourself
5. Try to get the highest score possible!

## Implementation Notes

This port recreates the core gameplay of the original VB6 version while using modern C++ and SDL3:

- `Direction` enum corresponds to the VB6 `Dir` enum
- `updateSnakePosition()` implements the VB6 `MainSequence` function
- `handleInput()` implements the VB6 `InputHandler` function
- Uses SDL3's event system instead of VB6's Windows messaging
- Simple colored rectangles instead of BMP sprites for portability

## Original VB6 Structure

The original game had these modules:
- `modGameEngine.bas` - Main game loop and movement
- `modVariables.bas` - Game state variables
- `modGamePlay.bas` - Gameplay logic
- Forms for UI and networking features

This port focuses on the core single-player snake gameplay.

## License

The original T-Snake 3 game is copyright T-RonX Modding. This is an educational port demonstrating SDL3 and C++ game development.
