#ifndef TIMER_H
#define TIMER_H


#include <iostream>
#include "SDL_include.h"

class Timer{

    public:
        Timer();
        void Update(float dt);
        void Restart();
        float Get();


    private:
        float time;


};


#endif