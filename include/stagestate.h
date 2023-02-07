#ifndef STAGESTATE_H
#define STAGESTATE_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "../include/music.h"
#include "../include/sprite.h"
#include "../include/gameobject.h"
#include "../include/state.h"
#include "../include/sound.h"
#include "../include/vec2.h"
#include "../include/tilemap.h"
#include "../include/text.h"
#include <string>
#include <array>
#include <memory>
#include <vector>



class StageState : public State {

    public:
        StageState();
        ~StageState();

        void LoadAssets();
        void Update(float dt);
        void Render();

        void Start();
        void Pause();
        void Resume();

    private:
        TileSet* tileSet;
        Music* backgroundMusic;
        Text* hp;
        Text* stamina;
        Text* mascara;



};

#endif