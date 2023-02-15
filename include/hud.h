#ifndef HUD_H
#define HUD_H


#include <iostream>
#include <vector>
#include <memory>
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "component.h"
#include "vec2.h"
#include "rect.h"
#include "sprite.h"



class GameObject;

class Hud : public Component{

    public:
        Hud(GameObject& associated, std::string file);
        ~Hud();


        void Start();
        
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        void NotifyCollision ( GameObject& other);

        void SetPos(Vec2 pos);
        void SetTexture(std::string file);


    private:

        Sprite* barra;

};


#endif