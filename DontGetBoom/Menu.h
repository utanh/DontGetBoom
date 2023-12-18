#ifndef MENU_H
#define MENU_H

#include "BaseMap.h"
#include "Button.h"

using namespace std;

#define MENU_MARGIN 10

#define MENU_HEIGHT  360
#define MENU_WIDTH   120

class Menu : public BaseMap{
    // Attributes
    private:
        Button size5, size4, size3, size2;
        Button quit;
        Button resume;

    // Constructor/Destructor
    public:
        Menu();
        ~Menu();

        void init(const int &w, const int &h, const int &x, const int &y, const char *bgr_path,
                                                                          const char *size5_path,
                                                                          const char *size4_path,
                                                                          const char *size3_path,
                                                                          const char *size2_path,
                                                                          const char *resume_path,
                                                                          const char *quit_path);
    
    // Getter/Setter

    // Event
        string handleEvents(uint32_t event_type) override;

    // Update
        void checkUpdated(const int &xmouse, const int &ymouse, uint32_t eventType) override;

    // Display
        void drawMap(SDL_Renderer *renderer) override;
};

#endif