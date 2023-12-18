#include "Game.h"
#include <windows.h> 
#include <unistd.h>

using namespace std;

int main(int argv, char** args){
    Game *game = nullptr;
    game = new Game();
    game->init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);

    while (game->running()){
        game->display();
        game->handleEvents();
        game->update();
    }

    game->clean();

    return 0;
}