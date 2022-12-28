/*
##############################
Esse codigo n esta sendo usado
##############################
*/

#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H


#include <iostream>
#include <vector>
#include <memory>
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "component.h"
#include "timer.h"
#include "vec2.h"

class GameObject;

class PenguinCannon : public Component{

    public:
        PenguinCannon(GameObject& associated, std::weak_ptr< GameObject > penguinBody);
        ~PenguinCannon();

        void Update (float dt);
        void Render ();
        bool Is (std::string type);

        void Shoot();

    private:
        std::weak_ptr< GameObject > pbody;
        float angle;
        float cooldown;
        Timer* timer;
};


#endif