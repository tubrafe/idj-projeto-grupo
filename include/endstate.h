#ifndef ENDSTATE_H
#define ENDSTATE_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "../include/music.h"
#include "../include/sprite.h"
#include "../include/gameobject.h"
#include "../include/state.h"
#include "../include/sound.h"
#include "../include/vec2.h"
#include <string>
#include <array>
#include <memory>
#include <vector>



class EndState : public State {

    public:
        
        EndState();
        ~EndState();
        
        void LoadAssets();
        void Update (float dt);
        void Render ();
        
        void Start();
        void Pause();
        void Resume(); 

    private:
        Music* backgroundMusic;

};

#endif