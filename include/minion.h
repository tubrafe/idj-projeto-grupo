/*
##############################
Esse codigo n esta sendo usado
##############################
*/

#ifndef MINION_H
#define MINION_H


#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "component.h"
#include "vec2.h"
#include <memory>
#include <vector>

class GameObject;

class Minion : public Component {

    public:
        Minion(GameObject& associated , std::weak_ptr< GameObject > alienCenter, float arcOffsetDeg = 0);
        
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void Shoot(Vec2 target);


    private:
        std::weak_ptr< GameObject > alienCenter; 
        float arc;
        Vec2 referencial;

};




#endif