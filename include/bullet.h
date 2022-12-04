#ifndef BULLET_H
#define BULLET_H


#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "component.h"
#include "vec2.h"


class GameObject;

class Bullet : public Component {

    public:
        Bullet(GameObject& associated , float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetsPlayer);
        
        void Update (float dt);
        void Render ();
        bool Is (std::string type);
        int GetDamage ();
        bool targetsPlayer;


    private:
        Vec2 speed;
        float distanceLeft;
        int damage;

};




#endif