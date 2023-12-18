#ifndef BASE_MAP_H
#define BASE_MAP_H

#include <SDL2/SDL.h>
#include <string>
#include <iostream>

using namespace std;

enum MAP_STATE {PAUSING, RUNNING};

class BaseMap{
    // Attributes
    protected:
        SDL_Rect rect;
        MAP_STATE state = RUNNING;

        const char *bgr_path;

        bool isUpdated = true;

    // Constructor/Destructor
    public:
        BaseMap();
        ~BaseMap();

        void init(const int &w, const int &h, const int &x, const int &y, const char *bgr_path);

    // Getter/Setter
    public:
        SDL_Rect get_xyhw();
        void set_xyhw(const int &x, const int &y, const int &h, const int &w);

        const char* get_bgrPath();
        void change_bgrPath(const char *bgr_path);

        MAP_STATE getMapState();
        void setMapState(MAP_STATE state);

        bool get_isUpdated();

    // Event
        virtual string handleEvents(uint32_t event_type) = 0;

    // Update
        virtual void checkUpdated(const int &xmouse, const int &ymouse, uint32_t eventType) = 0;

    // Display
        virtual void drawMap(SDL_Renderer *renderer) = 0;
};

#endif