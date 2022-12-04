#ifndef RECT_H
#define RECT_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "vec2.h"

class Rect {

    public:
        Rect();
        Rect(float d, float f, float j, float l);
        float x;
        float y;
        float w;
        float h;
        bool Contains(Vec2 vetor);
        Vec2 GetCenter();


};

#endif