#include "Game.h"

using namespace std;

Game::Game(){}
Game::~Game(){}

void Game::init(const char* title, const int &xpos, const int &ypos, const int &width, const int &height, const bool &fullscreen){
    // Create Game
    this->WIDTH = width;
    this->HEIGHT = height;
    this->isRunning = true;

    int flag;
    if (fullscreen)
        flag = SDL_WINDOW_FULLSCREEN;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        cout << "Subsystems Initialised!" << endl;

        this->window = SDL_CreateWindow(title, xpos, ypos, this->WIDTH, this->HEIGHT, flag);
        if (this->window){
            cout << "Window Created!" << endl;
        }
        else{
            cout << "Window can't create!" << endl;
            this->isRunning = false;
            return;
        }

        this->renderer = SDL_CreateRenderer(this->window, -1, 0);
        if (this->renderer){
            SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
            cout << "Renderer Created!" << endl;
        }
        else{
            cout << "Renderer can't create!" << endl;
            this->isRunning = false;
            return;
        }
    }
        
    // Create map
    this->menu = new Menu();
    int menu_x = (WINDOW_WIDTH - MENU_WIDTH) / 2;
    int menu_y = (WINDOW_HEIGHT - MENU_HEIGHT) / 2;
    this->menu->init(MENU_WIDTH, MENU_HEIGHT, menu_x, menu_y, MENU_BGR, SIZE5_IMG, SIZE4_IMG, SIZE3_IMG, SIZE2_IMG, RESUME_IMG, QUIT_IMG);

    this->mainMap = new Menu();
    this->mainMap = this->menu;
}

void Game::freeMenu(){  
    if (this->menu != nullptr){
        delete this->menu;
        this->menu = nullptr;
    }
}

void Game::freeGameOver(){  
    if (this->gameover != nullptr){
        delete this->gameover;
        this->gameover = nullptr;
    }
}

void Game::freePlayMap(){
    if (this->playmap != nullptr){
        delete this->playmap;
        this->playmap = nullptr;
    }
}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    
    int x, y;
    SDL_GetMouseState(&x, &y);
    mainMap->checkUpdated(x, y, event.type);

    switch (event.type)
    {
    case SDL_MOUSEBUTTONDOWN:{
        string next_process = mainMap->handleEvents(event.type);

        cout << next_process << endl;
        
        if (next_process == "NONE"){
            break;
        }
        // Go to new game
        else if (next_process == "SIZE2"){
            if (this->mapDisplaying == MENU){
                this->freeMenu();
                this->freePlayMap();
                
                this->playmap = new PlayMap();
                this->playmap->init(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, PLAYMAP_BGR, 2, 2, RECTS_IMG, PAUSE_IMG, QUIT_IMG, BOOM_IMG, FLIPPED_IMG);
                
                this->mainMap = new PlayMap();
                this->mainMap = this->playmap;
                this->mapDisplaying = PLAYMAP;
            }
        }
        else if (next_process == "SIZE3"){
            if (this->mapDisplaying == MENU){
                this->freeMenu();
                this->freePlayMap();
                
                this->playmap = new PlayMap();
                this->playmap->init(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, PLAYMAP_BGR, 3, 3, RECTS_IMG, PAUSE_IMG, QUIT_IMG, BOOM_IMG, FLIPPED_IMG);
                
                this->mainMap = new PlayMap();
                this->mainMap = this->playmap;
                this->mapDisplaying = PLAYMAP;
            }
        }
        else if (next_process == "SIZE4"){
            if (this->mapDisplaying == MENU){
                this->freeMenu();
                this->freePlayMap();
                
                this->playmap = new PlayMap();
                this->playmap->init(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, PLAYMAP_BGR, 4, 4, RECTS_IMG, PAUSE_IMG, QUIT_IMG, BOOM_IMG, FLIPPED_IMG);
                
                this->mainMap = new PlayMap();
                this->mainMap = this->playmap;
                this->mapDisplaying = PLAYMAP;
            }
        }
        else if (next_process == "SIZE5"){
            if (this->mapDisplaying == MENU){
                this->freeMenu();
                this->freePlayMap();
                
                this->playmap = new PlayMap();
                this->playmap->init(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, PLAYMAP_BGR, 5, 5, RECTS_IMG, PAUSE_IMG, QUIT_IMG, BOOM_IMG, FLIPPED_IMG);
                
                this->mainMap = new PlayMap();
                this->mainMap = this->playmap;
                this->mapDisplaying = PLAYMAP;
            }
        }
        // Go to menu
        else if (next_process == "PAUSE"){
            if (this->mapDisplaying == PLAYMAP){
                this->playmap->setMapState(PAUSING);
                
                this->menu = new Menu();
                int menu_x = (WINDOW_WIDTH - MENU_WIDTH) / 2;
                int menu_y = (WINDOW_HEIGHT - MENU_HEIGHT) / 2;
                this->menu->init(MENU_WIDTH, MENU_HEIGHT, menu_x, menu_y, MENU_BGR, SIZE5_IMG, SIZE4_IMG, SIZE3_IMG, SIZE2_IMG, RESUME_IMG, QUIT_IMG);
                
                this->mainMap = new Menu();
                this->mainMap = this->menu;
                this->mapDisplaying = MENU;
            }
        }
        // Continue game
        else if (next_process == "RESUME"){
            if (this->mapDisplaying == MENU && this->playmap != nullptr){
                this->freeMenu();
                
                this->playmap->setMapState(RUNNING);
                
                this->mainMap = new PlayMap();
                this->mainMap = this->playmap;
                this->mapDisplaying = PLAYMAP;
            }
        }
        // Quit game
        else if (next_process == "QUIT")
            this->isRunning = false;
        // Game over
        else if (next_process == "GAMEOVER"){
            if (this->mapDisplaying == PLAYMAP){
                this->playmap->setMapState(PAUSING);
                
                this->gameover = new GameOver();
                this->gameover->init(WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, PLAYMAP_BGR, this->playmap->get_boomButton(), NEWGAME_IMG);
            
                this->mainMap = new GameOver();
                this->mainMap = this->gameover;
                this->mapDisplaying = GAMEOVER;
            }
        }
        // Replay
        else if (next_process == "NEWGAME"){
            if (this->mapDisplaying == GAMEOVER){
                this->freeGameOver();
                this->freePlayMap();
                
                this->menu = new Menu();
                int menu_x = (WINDOW_WIDTH - MENU_WIDTH) / 2;
                int menu_y = (WINDOW_HEIGHT - MENU_HEIGHT) / 2;
                this->menu->init(MENU_WIDTH, MENU_HEIGHT, menu_x, menu_y, MENU_BGR, SIZE5_IMG, SIZE4_IMG, SIZE3_IMG, SIZE2_IMG, RESUME_IMG, QUIT_IMG);
                
                this->mainMap = new Menu();
                this->mainMap = this->menu;
                this->mapDisplaying = MENU;
            }
        }

        break;
    }
    case SDL_QUIT:{
        this->isRunning = false;
        break;
    }
    default:
        break;
    }
}

void Game::update(){
    count++;
}

void Game::clean(){
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    SDL_Quit();

    cout << "Game Cleaned!"  << endl;
}

bool Game::running(){
    return this->isRunning;
}

void Game::drawBGR(){
    SDL_Rect tempRect;
    
    tempRect.h = this->HEIGHT;
    tempRect.w = this->WIDTH;
    tempRect.x = 0;
    tempRect.y = 0;
    
    SDL_Surface* surface = SDL_LoadBMP(MAIN_BGR); 
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); 
    SDL_FreeSurface(surface);

    SDL_RenderCopy(renderer, texture, NULL, &tempRect);
}

void Game::display(){
    if (mainMap != nullptr && mainMap->getMapState() == RUNNING && mainMap->get_isUpdated() == true){
        this->drawBGR();
        mainMap->drawMap(this->renderer);
        
        SDL_RenderPresent(this->renderer);
    }
}