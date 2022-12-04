#include "../include/bloco.h"
#include "../include/state.h"
#include "../include/game.h"
#include "../include/collider.h"



Bloco :: Bloco(GameObject& associated,  std :: string file, float posx, float posy): Component(associated){


    Sprite* imagem = new Sprite(associated, file);
    associated.AddComponent(imagem);

    Collider* colisor = new Collider(associated);
    this->associated.AddComponent(colisor);


    associated.box.x = posx;
    associated.box.y = posy;




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


    return associated.box.h;


}



float Bloco :: getLength(){


    return associated.box.w;


}

float Bloco :: getX(){


    return associated.box.x;


}

float Bloco :: getY(){


    return associated.box.y;


}

Vec2 Bloco :: getcenter(){


    return associated.box.GetCenter();


}



bool Bloco::Contains(Vec2 vetor){


    return associated.box.Contains(vetor);


}