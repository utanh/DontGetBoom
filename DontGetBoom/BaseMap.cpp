#include "BaseMap.h"

using namespace std;

// ========================================================== Constructor/Destructor
BaseMap::BaseMap(){}
BaseMap::~BaseMap(){}

void BaseMap::init(const int &w, const int &h, const int &x, const int &y, const char *bgr_path){
    this->rect.h = h;
    this->rect.w = w;
    this->rect.x = x;
    this->rect.y = y;

    this->bgr_path = bgr_path;
}

// ========================================================== Getter/Setter
SDL_Rect BaseMap::get_xyhw(){
    return this->rect;
}

void BaseMap::set_xyhw(const int &x, const int &y, const int &h, const int &w){
    this->rect.h = h;
    this->rect.w = w;
    this->rect.x = x;
    this->rect.y = y;
}

const char* BaseMap::get_bgrPath(){
    return this->bgr_path;
}

void BaseMap::change_bgrPath(const char *bgr_path){
    this->bgr_path = bgr_path;
}

MAP_STATE BaseMap::getMapState(){
    return this->state;
}

void BaseMap::setMapState(MAP_STATE state){
    this->state = state;
}

bool BaseMap::get_isUpdated(){
    return isUpdated;
}