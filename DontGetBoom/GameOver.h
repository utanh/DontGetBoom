#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "BaseMap.h"
#include "Button.h"

using namespace std;

#define RECTS_MARGIN 10

#define RECTS_HEIGHT  500
#define RECTS_WIDTH   500

#define BUTTON_HEIGHT  40
#define BUTTON_WIDTH   100

class GameOver : public BaseMap{
    // Attributes
    private:
        Button boom_rect;

        Button newgame;

    // Constructor/Destructor
    public:
        GameOver();
        ~GameOver();

        void init(const int &w, const int &h, const int &x, const int &y, const char *bgr_path,
                                                                          const Button &boom_rect,
                                                                          const char *newgame_path);
    
    // Getter/Setter

    // Event
        string handleEvents(uint32_t event_type) override;

    // Update
        void checkUpdated(const int &xmouse, const int &ymouse, uint32_t eventType) override;

    // Display
        void drawMap(SDL_Renderer *renderer) override;
};

#endif