#ifndef COMPONENT_H
#define COMPONENT_H


#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"


class GameObject;

class Component {

    public:
        Component(GameObject& associated);


        virtual ~Component();
        void virtual Update(float dt) =0;
        void virtual Render() = 0;
        bool virtual Is(std :: string type) = 0;
        void virtual Start();

        void virtual NotifyCollision ( GameObject& other);


    protected:
        GameObject& associated;


};


#endif