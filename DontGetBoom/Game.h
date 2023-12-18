#ifndef GAME_H
#define GAME_H

#include "Menu.h"
#include "PlayMap.h"
#include "GameOver.h"
#include <iostream>

using namespace std;

#define WINDOW_HEIGHT   545
#define WINDOW_WIDTH    500

#define MAIN_BGR    "main_bgr.bmp"
#define MENU_BGR    "menu.bmp"
#define PLAYMAP_BGR "playmap.bmp"

#define QUIT_IMG    "quit.bmp"
#define RESUME_IMG  "resume.bmp"
#define PAUSE_IMG   "pause.bmp"
#define NEWGAME_IMG "newgame.bmp"

#define SIZE2_IMG   "size2.bmp"
#define SIZE3_IMG   "size3.bmp"
#define SIZE4_IMG   "size4.bmp"
#define SIZE5_IMG   "size5.bmp"

#define RECTS_IMG   "rects.bmp"
#define BOOM_IMG    "boom.bmp"
#define FLIPPED_IMG "flipped.bmp"

enum MAP_TYPE   {MENU, PLAYMAP, GAMEOVER};

class Game{
    // Atributes
    private:
        bool isRunning;
        
        SDL_Window *window;
        int HEIGHT, WIDTH;

        SDL_Renderer *renderer;

        MAP_TYPE mapDisplaying = MENU;
        BaseMap *mainMap = nullptr;
        Menu *menu = nullptr;
        GameOver *gameover = nullptr;
        PlayMap *playmap = nullptr;

        int count = 0;

    // Contructor/Destructor
    public:
        Game();
        ~Game();
        
        void init(const char* title, const int &xpos, const int &ypos, const int &width, const int &height, const bool &fullscreen);

    // Methods
    private:
        void freeMenu();
        void freeGameOver();
        void freePlayMap();

    public:
        void handleEvents();
        void update();
        void clean();

        bool running();

    // Draw
        void drawBGR();
        void display();
};

#endif /* GAME_H */