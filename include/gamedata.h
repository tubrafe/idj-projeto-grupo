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

        static int hp_atual;
        static int hp_total;

        static float stamina_atual;
        static float stamina_total;
};

#endif