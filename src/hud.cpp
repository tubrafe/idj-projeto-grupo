#include "../include/hud.h"
#include "../include/jogador.h"
#include "../include/sprite.h"
#include "../include/state.h"
#include "../include/game.h"


Hud :: Hud(GameObject& associated, std::string file) : Component(associated){

    barra = new Sprite(associated,file);

    associated.AddComponent(barra);

}

Hud :: ~Hud(){}


void Hud :: Start(){}        
void Hud :: Update(float dt){}
void Hud :: Render(){}

bool Hud :: Is(std::string type){

    
    if (type == "Hud"){
        return true;
    };
    return false;


}


void Hud :: NotifyCollision ( GameObject& other){}



void Hud :: SetPos(Vec2 pos){

    barra->SetPos(pos);


}


void Hud :: SetTexture(std::string file){

    barra->setTexture(file);


}