#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"

class Vec2 {

    public:
        Vec2();
        Vec2(float d, float j) ;
        float x;
        float y;
        Vec2 GetRotated(float ang);
        Vec2 operator+ (Vec2 primeiro);
        Vec2 operator- (Vec2 primeiro);
        Vec2 operator* (Vec2 primeiro);
        Vec2 normalizar();
        float magnitude();
        friend Vec2 operator* (Vec2 const &vec2, float multiplicando);


};

#endif