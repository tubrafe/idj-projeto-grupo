#ifndef JOGADOR_H
#define JOGADOR_H


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

class Jogador : public Component{

    public:
        Jogador(GameObject& associated);
        ~Jogador();

        void Update (float dt);
        void Render ();
        bool Is (std::string type);
        void Start();

        static Jogador* player;

        void NotifyCollision ( GameObject& other);

        Rect GetPos();

    private:
        Vec2 speed;
        float linearSpeed;
        float angle;
        int hp;

        int gravidade;
        int gravidadeMax;
        int velPulo;

        Timer* encostar;
        Timer* invuneravel;
        int contato;

        bool caindo;
        bool parado;
        bool agarrado;
        int ladoGrudado;

        int numJumps;
        int pulosRestantes;

        float posyh_anterior;
        float posy_anterior;

};


#endif