#include "Menu.h"

using namespace std;

// Constructor/Destructor
Menu::Menu(){}
Menu::~Menu(){}

void Menu::init(const int &w, const int &h, const int &x, const int &y, const char *bgr_path,
                                                                        const char *size5_path,
                                                                        const char *size4_path,
                                                                        const char *size3_path,
                                                                        const char *size2_path,
                                                                        const char *resume_path,
                                                                        const char *quit_path){
    this->BaseMap::init(w, h, x, y, bgr_path);

    int w_button = rect.w - 2 * MENU_MARGIN;
    int h_button = (rect.h - 7 * MENU_MARGIN) / 6;
    int button_x = rect.x + MENU_MARGIN;

    int size5_y = rect.y + MENU_MARGIN;
    this->size5.init(w_button, h_button, button_x, size5_y, size5_path);

    int size4_y = size5_y + MENU_MARGIN + h_button;
    this->size4.init(w_button, h_button, button_x, size4_y, size4_path);

    int size3_y = size4_y + MENU_MARGIN + h_button;
    this->size3.init(w_button, h_button, button_x, size3_y, size3_path);

    int size2_y = size3_y + MENU_MARGIN + h_button;
    this->size2.init(w_button, h_button, button_x, size2_y, size2_path);

    int quit_y = size2_y + MENU_MARGIN + h_button;
    this->quit.init(w_button, h_button, button_x, quit_y, quit_path);

    int resume_y = quit_y + MENU_MARGIN + h_button;
    this->resume.init(w_button, h_button, button_x, resume_y, resume_path);
}

// Getter/Setter

// Event
string Menu::handleEvents(uint32_t event_type){
    if (size5.checkMouseDownInButton())
        return "SIZE5";
    else if (size4.checkMouseDownInButton())
        return "SIZE4";
    else if (size3.checkMouseDownInButton())
        return "SIZE3";
    else if (size2.checkMouseDownInButton())
        return "SIZE2";
    else if (quit.checkMouseDownInButton())
        return "QUIT";
    else if (resume.checkMouseDownInButton())
        return "RESUME";
    else
        return "NONE";
}

// Update
void Menu::checkUpdated(const int &xmouse, const int &ymouse, uint32_t eventType){
    this->isUpdated = size5.isAnyChangeState(xmouse, ymouse, eventType) 
                    || size4.isAnyChangeState(xmouse, ymouse, eventType)
                    || size3.isAnyChangeState(xmouse, ymouse, eventType)
                    || size2.isAnyChangeState(xmouse, ymouse, eventType)
                    || quit.isAnyChangeState(xmouse, ymouse, eventType)
                    || resume.isAnyChangeState(xmouse, ymouse, eventType);
}

// Display
void Menu::drawMap(SDL_Renderer *renderer){
    if (!this->isUpdated)
        return;

    SDL_Rect tempRect = this->rect;
    SDL_Surface* surface = SDL_LoadBMP(this->bgr_path); 
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); 
    SDL_RenderCopy(renderer, texture, NULL, &tempRect);

    tempRect = this->size5.getRectFitState();
    surface = SDL_LoadBMP(this->size5.get_imgPath()); 
    texture = SDL_CreateTextureFromSurface(renderer, surface); 
    SDL_RenderCopy(renderer, texture, NULL, &tempRect);

    tempRect = this->size4.getRectFitState();
    surface = SDL_LoadBMP(this->size4.get_imgPath()); 
    texture = SDL_CreateTextureFromSurface(renderer, surface); 
    SDL_RenderCopy(renderer, texture, NULL, &tempRect);

    tempRect = this->size3.getRectFitState();
    surface = SDL_LoadBMP(this->size3.get_imgPath()); 
    texture = SDL_CreateTextureFromSurface(renderer, surface); 
    SDL_RenderCopy(renderer, texture, NULL, &tempRect);

    tempRect = this->size2.getRectFitState();
    surface = SDL_LoadBMP(this->size2.get_imgPath()); 
    texture = SDL_CreateTextureFromSurface(renderer, surface); 
    SDL_RenderCopy(renderer, texture, NULL, &tempRect);

    tempRect = this->quit.getRectFitState();
    surface = SDL_LoadBMP(this->quit.get_imgPath()); 
    texture = SDL_CreateTextureFromSurface(renderer, surface); 
    SDL_RenderCopy(renderer, texture, NULL, &tempRect);

    tempRect = this->resume.getRectFitState();
    surface = SDL_LoadBMP(this->resume.get_imgPath()); 
    texture = SDL_CreateTextureFromSurface(renderer, surface); 
    SDL_RenderCopy(renderer, texture, NULL, &tempRect);

    SDL_FreeSurface(surface);
}