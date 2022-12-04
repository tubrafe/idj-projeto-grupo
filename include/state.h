#ifndef STATE_H
#define STATE_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "../include/music.h"
#include "../include/sprite.h"
#include "../include/gameobject.h"
#include "../include/sound.h"
#include "../include/vec2.h"
#include "../include/tilemap.h"
#include <string>
#include <array>
#include <memory>
#include <vector>



class State {

    public:
        State();
        virtual ~State();

        virtual void LoadAssets() = 0;
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;


        void virtual Start() = 0;
        void virtual Pause() = 0;
        void virtual Resume() = 0;

        virtual std::weak_ptr< GameObject > AddObject(GameObject* go); 
        virtual std::weak_ptr< GameObject > GetObjectPtr(GameObject* go); 

        bool QuitRequested();
        bool PopRequested();

    protected:
        void StartArray();
        void virtual UpdateArray(float dt);    
        void virtual RenderArray();

        bool quitRequested; 
        std::vector< std::shared_ptr< GameObject > >  objectArray;
        bool started;
        bool popRequested;

};

#endif