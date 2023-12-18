#include "GameOver.h"

using namespace std;

GameOver::GameOver(){}
GameOver::~GameOver(){}

void GameOver::init(const int &w, const int &h, const int &x, const int &y, const char *bgr_path,
                                                                            const Button &boom_rect,
                                                                            const char *newgame_path){
    this->BaseMap::init(w, h, x, y, bgr_path);

    this->boom_rect = boom_rect;

    int newgame_x = (w - BUTTON_WIDTH) / 2;
    int newgame_y = RECTS_HEIGHT;
    this->newgame.init(BUTTON_WIDTH, BUTTON_HEIGHT, newgame_x, newgame_y, newgame_path);
}
    
// Getter/Setter

// Event
string GameOver::handleEvents(uint32_t event_type){
    if (newgame.checkMouseDownInButton())
        return "NEWGAME";
    
    return "NONE";
}

// Update
void GameOver::checkUpdated(const int &xmouse, const int &ymouse, uint32_t eventType){
    this->isUpdated = this->newgame.isAnyChangeState(xmouse, ymouse, eventType)
                    || this->boom_rect.isAnyChangeState(xmouse, ymouse, eventType);
}

// Display
void GameOver::drawMap(SDL_Renderer *renderer){
    if (!this->isUpdated)
        return;

    // Draw BGR
    SDL_Rect tempRect = this->rect;
    SDL_Surface* surface = SDL_LoadBMP(this->bgr_path); 
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); 
    SDL_RenderCopy(renderer, texture, NULL, &tempRect);

    // Draw newgame button
    tempRect = this->newgame.getRectFitState();
    surface = SDL_LoadBMP(this->newgame.get_imgPath()); 
    texture = SDL_CreateTextureFromSurface(renderer, surface); 
    SDL_RenderCopy(renderer, texture, NULL, &tempRect);

    // Draw boom rect
    tempRect = this->boom_rect.getRectFitState();
    surface = SDL_LoadBMP(this->boom_rect.get_imgPath()); 
    texture = SDL_CreateTextureFromSurface(renderer, surface); 
    SDL_RenderCopy(renderer, texture, NULL, &tempRect);
}