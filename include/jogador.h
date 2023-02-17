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
#include "sound.h"
#include "hud.h"


class GameObject;

class Jogador : public Component{

    public:
        Jogador(GameObject& associated, Hud* hud);
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
        bool anima_grudado;
        int ladoGrudado;
        int speed_anterior;
        bool ladoVirado;

        Timer* dash_cd;
        bool dash;
        bool anima_dash;

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

        Sound* sons;

        bool damaged;
        bool caiu;

        Hud* barra_vida;

        int velocidade_anterior;

        Timer* gas_timer;
        bool dano_gas;


};


#endif