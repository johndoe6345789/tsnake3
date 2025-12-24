#include "game.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "T-Snake 3 - SDL3/C++ Port" << std::endl;
    std::cout << "Copyright © 2005 T-RonX Modding (Original VB6 version)" << std::endl;
    std::cout << "Ported to SDL3/C++ in 2025" << std::endl;
    std::cout << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  Arrow Keys or WASD - Move snake" << std::endl;
    std::cout << "  ESC - Quit game" << std::endl;
    std::cout << std::endl;
    
    Game game;
    
    if (!game.init()) {
        std::cerr << "Failed to initialize game!" << std::endl;
        return 1;
    }
    
    game.run();
    
    return 0;
}
