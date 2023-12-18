#include "PlayMap.h"
#include <time.h>

using namespace std;

PlayMap::PlayMap(){}
PlayMap::~PlayMap(){}

void PlayMap::init(const int &w, const int &h, const int &x, const int &y, const char *bgr_path,
                                       const int &n_row, const int &n_col, const char *rects_path,
                                                                           const char *pause_path,
                                                                           const char *quit_path,
                                                                           const char *boom_path,
                                                                           const char *flipped_path){
    // Init BaseMap
    this->BaseMap::init(w, h, x, y, bgr_path);

    // Init n_row & n_col
    this->n_row = n_row;
    this->n_col = n_col;

    // Init boom
    this->boom_path = boom_path;
    srand(time(NULL));
    this->boom_idx = rand() % (n_row * n_col);

    // Init rects
    int rect_w = (RECTS_WIDTH - (this->n_col + 1) * RECTS_MARGIN) / n_col;
    int rect_h = (RECTS_HEIGHT - (this->n_row + 1) * RECTS_MARGIN) / n_row; 
    
    for (int i = 0; i < n_row; i++)
        for (int j = 0; j < n_col; j++){
            int x_ij = i * (rect_w + RECTS_MARGIN) + RECTS_MARGIN;
            int y_ij = j * (rect_h + RECTS_MARGIN) + RECTS_MARGIN;
            this->rects[i][j].init(rect_w, rect_h, x_ij, y_ij, rects_path);
        }
    
    this->flipped_path = flipped_path;

    // Init pause button
    int pause_x = RECTS_MARGIN;
    int pause_y = RECTS_HEIGHT;
    this->pause.init(BUTTON_WIDTH, BUTTON_HEIGHT, pause_x, pause_y, pause_path);

    // Init quit button
    int quit_x = RECTS_WIDTH - RECTS_MARGIN - BUTTON_WIDTH;
    int quit_y = RECTS_HEIGHT;
    this->quit.init(BUTTON_WIDTH, BUTTON_HEIGHT, quit_x, quit_y, quit_path);
}
    
// Getter/Setter
Button PlayMap::get_boomButton(){
    return rects[boom_idx / n_row][boom_idx % n_col];
}

// Event
bool PlayMap::checkGameOver(const int &i_MOUSEDOWN, const int &j_MOUSEDOWN){
    if ((i_MOUSEDOWN * n_row + j_MOUSEDOWN) == this->boom_idx)
        return true;

    return false;
}
string PlayMap::handleEvents(uint32_t event_type){
    if (pause.checkMouseDownInButton())
        return "PAUSE";
    else if (quit.checkMouseDownInButton())
        return "QUIT";
        
    for (int i = 0; i < n_row; i++)
        for (int j = 0; j < n_col; j++){
            if (this->rects[i][j].checkMouseDownInButton()){
                if (checkGameOver(i, j)){
                    this->rects[boom_idx / n_row][boom_idx % n_row].change_imgPath(boom_path);
                    return "GAMEOVER";
                }
                else
                    this->rects[i][j].change_imgPath(flipped_path);
            }
        }

    return "NONE";
}

// Update
void PlayMap::checkUpdated(const int &xmouse, const int &ymouse, uint32_t eventType){
    this->isUpdated = pause.isAnyChangeState(xmouse, ymouse, eventType)
                    || quit.isAnyChangeState(xmouse, ymouse, eventType);
    
    for (int i = 0; i < n_row; i++)
        for (int j = 0; j < n_col; j++)
            this->isUpdated = this->isUpdated || this->rects[i][j].isAnyChangeState(xmouse, ymouse, eventType);
}

// Display
void PlayMap::drawMap(SDL_Renderer *renderer){
    if (!this->isUpdated)
        return;

    // Draw BGR
    SDL_Rect tempRect = this->rect;
    SDL_Surface* surface = SDL_LoadBMP(this->bgr_path); 
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); 
    SDL_RenderCopy(renderer, texture, NULL, &tempRect);

    // Draw rects
    for (int i = 0; i < n_row; i++)
        for (int j = 0; j < n_col; j++){
            tempRect = this->rects[i][j].getRectFitState();
            surface = SDL_LoadBMP(this->rects[i][j].get_imgPath()); 
            texture = SDL_CreateTextureFromSurface(renderer, surface); 
            SDL_RenderCopy(renderer, texture, NULL, &tempRect);
        }

    // Draw pause button
    tempRect = this->pause.getRectFitState();
    surface = SDL_LoadBMP(this->pause.get_imgPath()); 
    texture = SDL_CreateTextureFromSurface(renderer, surface); 
    SDL_RenderCopy(renderer, texture, NULL, &tempRect);

    // Draw quit button
    tempRect = this->quit.getRectFitState();
    surface = SDL_LoadBMP(this->quit.get_imgPath()); 
    texture = SDL_CreateTextureFromSurface(renderer, surface); 
    SDL_RenderCopy(renderer, texture, NULL, &tempRect);

    SDL_FreeSurface(surface);
}