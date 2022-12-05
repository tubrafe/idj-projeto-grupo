#ifndef COLLIDER_H
#define COLLIDER_H


#include <iostream>
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "component.h"
#include "vec2.h"
#include "rect.h"
#include "../src/Collision.cpp"

class GameObject;

class Collider : public Component{

    public:
        Collider(GameObject& associated, Vec2 scale  = {1, 1}, Vec2 offset = {0, 0});
        
        void Update (float dt);
        void Render ();
        bool Is (std::string type);

        void SetScale (Vec2 scale);
        void SetOffset (Vec2 offset);   

        bool IsColliding(Collider colisor);     
            
        Rect box;


    private:

        Vec2 scale;
        Vec2 offset; 




};


#endif