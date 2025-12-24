#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <random>

// Direction enumeration (similar to VB6 Dir enum)
enum class Direction {
    Up,
    Down,
    Left,
    Right
};

// Position structure
struct Position {
    int x;
    int y;
    
    Position(int x = 0, int y = 0) : x(x), y(y) {}
    
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

// Snake segment structure
struct SnakeSegment {
    Position position;
    SDL_FRect rect;
    
    SnakeSegment(int x, int y, int size = 10) 
        : position(x, y), rect{(float)x, (float)y, (float)size, (float)size} {}
};

// Main Game class
class Game {
public:
    Game();
    ~Game();
    
    bool init();
    void run();
    void cleanup();
    
private:
    // Initialization
    bool initSDL();
    bool loadAssets();
    
    // Game loop functions
    void handleEvents();
    void update();
    void render();
    
    // Input handling (equivalent to InputHandler in VB6)
    void handleInput(SDL_Keycode keyCode);
    
    // Game logic (equivalent to MainSequence in VB6)
    void updateSnakePosition();
    void addSnakeSegment();
    bool checkCollision();
    void spawnFood();
    
    // Rendering functions
    void renderSnake();
    void renderFood();
    
    // SDL components
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    // Game state
    bool running;
    Direction currentDirection;
    Direction nextDirection;
    std::vector<SnakeSegment> snake;
    Position food;
    
    // Game settings
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const int SEGMENT_SIZE = 10;
    const int INITIAL_SNAKE_LENGTH = 3;
    const int GAME_SPEED = 100; // milliseconds per frame
    
    // Timing
    Uint64 lastUpdateTime;
    
    // Score
    int score;
    
    // Random number generator for food spawning
    std::random_device rd;
    std::mt19937 gen;
};

#endif // GAME_H
