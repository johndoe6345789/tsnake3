#include "game.h"
#include <iostream>
#include <random>

Game::Game() 
    : window(nullptr)
    , renderer(nullptr)
    , running(false)
    , currentDirection(Direction::Right)
    , nextDirection(Direction::Right)
    , lastUpdateTime(0)
    , score(0)
    , gen(rd()) {
}

Game::~Game() {
    cleanup();
}

bool Game::init() {
    if (!initSDL()) {
        return false;
    }
    
    // Initialize snake
    snake.clear();
    int startX = WINDOW_WIDTH / 2;
    int startY = WINDOW_HEIGHT / 2;
    
    for (int i = 0; i < INITIAL_SNAKE_LENGTH; i++) {
        snake.push_back(SnakeSegment(startX - i * SEGMENT_SIZE, startY, SEGMENT_SIZE));
    }
    
    // Spawn initial food
    spawnFood();
    
    lastUpdateTime = SDL_GetTicks();
    running = true;
    
    return true;
}

bool Game::initSDL() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow(
        "T-Snake 3 - SDL3/C++ Port",
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );
    
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    
    return true;
}

bool Game::loadAssets() {
    // For simplicity, we're using solid colors instead of BMP sprites
    // In a full implementation, you could load the original BMP files
    return true;
}

void Game::run() {
    while (running) {
        handleEvents();
        
        Uint64 currentTime = SDL_GetTicks();
        if (currentTime - lastUpdateTime >= GAME_SPEED) {
            update();
            lastUpdateTime = currentTime;
        }
        
        render();
        SDL_Delay(1); // Small delay to prevent CPU spinning
    }
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
            handleInput(event.key.key);
        }
    }
}

void Game::handleInput(SDL_Keycode keyCode) {
    // Handle input similar to VB6 InputHandler
    // Prevent snake from reversing into itself
    switch (keyCode) {
        case SDLK_UP:
        case SDLK_W:
            if (currentDirection != Direction::Down) {
                nextDirection = Direction::Up;
            }
            break;
            
        case SDLK_DOWN:
        case SDLK_S:
            if (currentDirection != Direction::Up) {
                nextDirection = Direction::Down;
            }
            break;
            
        case SDLK_LEFT:
        case SDLK_A:
            if (currentDirection != Direction::Right) {
                nextDirection = Direction::Left;
            }
            break;
            
        case SDLK_RIGHT:
        case SDLK_D:
            if (currentDirection != Direction::Left) {
                nextDirection = Direction::Right;
            }
            break;
            
        case SDLK_ESCAPE:
            running = false;
            break;
    }
}

void Game::update() {
    currentDirection = nextDirection;
    
    updateSnakePosition();
    
    // Check for food collision
    if (snake[0].position == food) {
        score += 10;
        addSnakeSegment();
        spawnFood();
    }
    
    // Check for game over conditions
    if (checkCollision()) {
        std::cout << "Game Over! Score: " << score << std::endl;
        running = false;
    }
}

void Game::updateSnakePosition() {
    // MainSequence equivalent - update snake position based on direction
    Position newHeadPos = snake[0].position;
    
    switch (currentDirection) {
        case Direction::Up:
            newHeadPos.y -= SEGMENT_SIZE;
            break;
            
        case Direction::Down:
            newHeadPos.y += SEGMENT_SIZE;
            break;
            
        case Direction::Left:
            newHeadPos.x -= SEGMENT_SIZE;
            break;
            
        case Direction::Right:
            newHeadPos.x += SEGMENT_SIZE;
            break;
    }
    
    // Move body segments (from tail to head)
    for (size_t i = snake.size() - 1; i > 0; i--) {
        snake[i].position = snake[i - 1].position;
        snake[i].rect.x = (float)snake[i].position.x;
        snake[i].rect.y = (float)snake[i].position.y;
    }
    
    // Update head
    snake[0].position = newHeadPos;
    snake[0].rect.x = (float)newHeadPos.x;
    snake[0].rect.y = (float)newHeadPos.y;
}

void Game::addSnakeSegment() {
    // Add new segment at the tail position
    Position lastPos = snake[snake.size() - 1].position;
    snake.push_back(SnakeSegment(lastPos.x, lastPos.y, SEGMENT_SIZE));
}

bool Game::checkCollision() {
    // Check wall collision
    if (snake[0].position.x < 0 || snake[0].position.x >= WINDOW_WIDTH ||
        snake[0].position.y < 0 || snake[0].position.y >= WINDOW_HEIGHT) {
        return true;
    }
    
    // Check self collision
    for (size_t i = 1; i < snake.size(); i++) {
        if (snake[0].position == snake[i].position) {
            return true;
        }
    }
    
    return false;
}

void Game::spawnFood() {
    std::uniform_int_distribution<> distX(0, (WINDOW_WIDTH / SEGMENT_SIZE) - 1);
    std::uniform_int_distribution<> distY(0, (WINDOW_HEIGHT / SEGMENT_SIZE) - 1);
    
    bool validPosition = false;
    while (!validPosition) {
        food.x = distX(gen) * SEGMENT_SIZE;
        food.y = distY(gen) * SEGMENT_SIZE;
        
        validPosition = true;
        // Make sure food doesn't spawn on snake
        for (const auto& segment : snake) {
            if (segment.position == food) {
                validPosition = false;
                break;
            }
        }
    }
}

void Game::render() {
    // Clear screen with black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    renderSnake();
    renderFood();
    
    SDL_RenderPresent(renderer);
}

void Game::renderSnake() {
    // Render snake head in green
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &snake[0].rect);
    
    // Render snake body in lighter green
    SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
    for (size_t i = 1; i < snake.size(); i++) {
        SDL_RenderFillRect(renderer, &snake[i].rect);
    }
}

void Game::renderFood() {
    // Render food in red
    SDL_FRect foodRect = {(float)food.x, (float)food.y, (float)SEGMENT_SIZE, (float)SEGMENT_SIZE};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &foodRect);
}

void Game::cleanup() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    
    SDL_Quit();
}
