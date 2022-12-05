#include "../include/bloco.h"
#include "../include/state.h"
#include "../include/game.h"




Bloco :: Bloco(GameObject& associated,  std :: string file, float posx, float posy, std::string tipo, Vec2 escala): Component(associated){

    associated.box.x = posx;
    associated.box.y = posy;

    Sprite* imagem = new Sprite(associated, file);
    imagem->SetScaleX(escala.x, escala.y);

    associated.AddComponent(imagem);

    Collider* colisor = new Collider(associated);

    float offx = (-1) *((escala.x - 1)*(imagem->GetWidth()/escala.x)/2);
    float offy = (-1) *((escala.y - 1)*(imagem->GetHeight()/escala.y)/2);

    colisor->SetOffset(Vec2(offx,offy));
    colisor->SetScale(escala);
    this->associated.AddComponent(colisor);

    this->colisor = colisor;


    this->tipo = tipo;




}


Bloco :: ~Bloco(){}


void Bloco :: Start(){}



void Bloco :: Update(float dt){}



void Bloco :: Render(){}
        
        
bool Bloco :: Is(std::string type){

    if (type == "Bloco"){
        return true;
    };
    return false;

}
   
   
   
void Bloco :: NotifyCollision ( GameObject& other){}



float Bloco :: getHigh(){


    return colisor->box.h;


}



float Bloco :: getLength(){


    return colisor->box.w;


}

float Bloco :: getX(){


    return colisor->box.x;


}

float Bloco :: getY(){


    return colisor->box.y;


}

Vec2 Bloco :: getcenter(){


    return associated.box.GetCenter();


}



bool Bloco::Contains(Vec2 vetor){


    return colisor->box.Contains(vetor);


}




std::string Bloco:: getTipo(){

    return tipo;


}