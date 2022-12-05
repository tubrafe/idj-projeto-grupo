#ifndef BLOCO_H
#define BLOCO_H


#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "component.h"
#include "vec2.h"
#include "sprite.h"
#include "collider.h"
#include <memory>
#include <vector>
#include <queue>

class GameObject;

class Bloco : public Component {

    public:
        Bloco(GameObject& associated,  std :: string file, float posx, float posy, std::string tipo, Vec2 escala);
        ~Bloco();
        void Start();
        
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void NotifyCollision ( GameObject& other);

        float getHigh();
        float getLength();
        float getY();
        float getX();
        Vec2 getcenter();

        bool Contains(Vec2 vetor);

        std::string getTipo();


    private:

        std::string tipo;

        Collider* colisor;
};




#endif