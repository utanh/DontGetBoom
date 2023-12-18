#include "Button.h"

// ============================================================== Constructor/Destructor

Button::Button(){}
Button::~Button(){}

void Button::init(const int &w, const int &h, const int &x, const int &y, const char *img_path){
    this->rect.h = h;
    this->rect.w = w;
    this->rect.x = x;
    this->rect.y = y;

    this->img_path = img_path;
}

// ============================================================== Getter/Setter

SDL_Rect Button::get_xyhw(){
    return this->rect;
}

void Button::set_xyhw(const int &x, const int &y, const int &h, const int &w){
    this->rect.h = h;
    this->rect.w = w;
    this->rect.x = x;
    this->rect.y = y;
}

const char* Button::get_imgPath(){
    return this->img_path;
}

void Button::change_imgPath(const char *img_path){
    this->img_path = img_path;
}

// ============================================================== Mouse-Button Relation

bool Button::isChangePos_MouseToButton(const int &xmouse, const int &ymouse){
    if (this->mouse_pos == NONE_POS)
        return false;

    if (rect.x <= xmouse && xmouse < rect.x + rect.w && rect.y <= ymouse && ymouse < rect.y + rect.h){
        if (this->mouse_pos != MOUSE_IN){
            this->mouse_pos = MOUSE_IN;
            return true;
        }
    }
    else{
        if (this->mouse_pos != MOUSE_OUT){
            this->mouse_pos = MOUSE_OUT;
            return true;
        }
    }
    
    return false;
}

bool Button::isChangeEvent_MouseToButton(uint32_t eventType){
    if (this->mouse_pos != MOUSE_IN)
        return false;

    if (eventType == SDL_MOUSEBUTTONDOWN){
        if (this->mouse_event != MOUSE_DOWN){
            this->mouse_event = MOUSE_DOWN;
            return true;
        }
    }
    else if (eventType == SDL_MOUSEBUTTONUP){
        if (this->mouse_event != MOUSE_UP){
            this->mouse_event = MOUSE_UP;
            return true;
        }
    }
    else {
        if (this->mouse_event != NONE_EVENT){
            this->mouse_event = NONE_EVENT;
            return true;
        }
    }

    return false;
}
    

SDL_Rect Button::getRectFitState(){
    SDL_Rect temp = this->rect;

    if (this->mouse_pos == MOUSE_IN && this->mouse_event == NONE_EVENT){
        temp.x -= 5;
        temp.y -= 5;
        temp.h += 10;
        temp.w += 10;
    }
    else if (this->mouse_pos == MOUSE_IN && this->mouse_event == MOUSE_DOWN){
        temp.x += 5;
        temp.y += 5;
        temp.h -= 10;
        temp.w -= 10;
    }

    return temp;
}

bool Button::isAnyChangeState(const int &xmouse, const int &ymouse, uint32_t eventType){
    if (isChangePos_MouseToButton(xmouse, ymouse) || isChangeEvent_MouseToButton(eventType)){
        getRectFitState();
        return true;
    }

    return false;
}

// ============================================================== Check mouse down in button

bool Button::checkMouseDownInButton(){
    if (this->mouse_pos == MOUSE_IN && this->mouse_event == MOUSE_DOWN)
        return true;
    
    return false;
}