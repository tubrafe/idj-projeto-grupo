#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"

class GameData {
    public:
        static bool playerVictory;
        static float checkPointX;
        static float checkPointY;
};

#endif