#ifndef PLAY_MAP_H
#define PLAY_MAP_H

#include "BaseMap.h"
#include "Button.h"

using namespace std;

#define RECTS_MARGIN 10

#define RECTS_HEIGHT  500
#define RECTS_WIDTH   500

#define BUTTON_HEIGHT  40
#define BUTTON_WIDTH   100

class PlayMap : public BaseMap{
    // Attributes
    private:
        Button rects[5][5];
        int n_row = 0;
        int n_col = 0;

        Button quit;
        Button pause;

        const char *boom_path;
        int boom_idx;

        const char *flipped_path;

    // Constructor/Destructor
    public:
        PlayMap();
        ~PlayMap();

        void init(const int &w, const int &h, const int &x, const int &y, const char *bgr_path,
                                      const int &n_row, const int &n_col, const char *rects_path,
                                                                          const char *pause_path,
                                                                          const char *quit_path,
                                                                          const char *boom_path,
                                                                          const char *flipped_path);
    
    // Getter/Setter
        Button get_boomButton();
    // Event
        bool checkGameOver(const int &i_MOUSEDOWN, const int &j_MOUSEDOWN);
        string handleEvents(uint32_t event_type) override;

    // Update
        void checkUpdated(const int &xmouse, const int &ymouse, uint32_t eventType) override;

    // Display
        void drawMap(SDL_Renderer *renderer) override;
};

#endif