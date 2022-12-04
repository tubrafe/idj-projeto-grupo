#ifndef PENGUINBODY_H
#define PENGUINBODY_H


#include <iostream>
#include <vector>
#include <memory>
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "component.h"
#include "vec2.h"
#include "rect.h"
#include "timer.h"


class GameObject;

class PenguinBody : public Component{

    public:
        PenguinBody(GameObject& associated);
        ~PenguinBody();

        void Update (float dt);
        void Render ();
        bool Is (std::string type);
        void Start();

        static PenguinBody* player;

        void NotifyCollision ( GameObject& other);

        Rect GetPos();

    private:
        std::weak_ptr< GameObject > pcannon;
        Vec2 speed;
        float linearSpeed;
        float angle;
        int hp;
        Timer* encostar;
        Timer* invuneravel;
        int aconteceu;
        bool caindo;

};


#endif