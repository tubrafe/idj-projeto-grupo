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
#include "bloco.h"


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

        void movimentacaoTipoChao(Bloco *chao);

    private:
        Vec2 speed;
        float atrito;
        float angle;

        int gravidade;
        int gravidadeMax;
        int velPulo;

        Timer* cd_hp;
        Timer* cd_stamina;
        float stamina;

        Timer* encostar;
        Timer* invuneravel;
        int contato;

        bool caindo;
        bool parado;
        bool andandod;
        bool andandoe;
        bool agarrado;
        bool pulando;
        bool anima_caindo;
        int ladoGrudado;
        int speed_anterior;

        int numJumps;
        int pulosRestantes;

        float posyh_anterior;
        float posy_anterior;

        float ultimoContatoX;
        float ultimoContatoY;

        Vec2 checkpoint;
        int mascara;

        float altura;
        float largura;

};


#endif