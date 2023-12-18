#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>

enum MOUSE_POSITION_TO_BUTTON {MOUSE_IN, MOUSE_OUT, NONE_POS}; 
// MOUSE_IN: mouse's position is in button
// MOUSE_OUT: mouse's position is out button
// NONE: this button isn't using

enum MOUSE_EVENT_IN_BUTTON {MOUSE_DOWN, MOUSE_UP, NONE_EVENT};

class Button{
    // Attributes
    private:
        SDL_Rect rect;
        MOUSE_POSITION_TO_BUTTON mouse_pos = MOUSE_OUT;
        MOUSE_EVENT_IN_BUTTON mouse_event = NONE_EVENT;

        const char *img_path;
    
    // Construction/Destructor
    public:
        Button();
        ~Button();

        void init(const int &w, const int &h, const int &x, const int &y, const char *img_path);
    
    // Getter/Setter
    public:
        SDL_Rect get_xyhw();
        void set_xyhw(const int &x, const int &y, const int &h, const int &w);

        const char* get_imgPath();
        void change_imgPath(const char *img_path);

    // Mouse-Button relation
    public:
        bool isChangePos_MouseToButton(const int &xmouse, const int &ymouse);
        // Return true if mouse_pos change.
        bool isChangeEvent_MouseToButton(uint32_t eventType);
        // Return true if mouse_event change.
        SDL_Rect getRectFitState();    

        bool isAnyChangeState(const int &xmouse, const int &ymouse, uint32_t eventType);

    // Check mouse down in button
        bool checkMouseDownInButton();
};

#endif