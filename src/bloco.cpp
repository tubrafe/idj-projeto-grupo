#include "../include/bloco.h"
#include "../include/state.h"
#include "../include/game.h"
#include "../include/jogador.h"
#include "../include/inputmanager.h"
#include "../include/gamedata.h"




Bloco :: Bloco(GameObject& associated,  std :: string file, float posx, float posy, std::string tipo, Vec2 escala): Component(associated){

    associated.box.x = posx;
    associated.box.y = posy;

// pega a imagem, podendo aumenta-la ou diminuia-la//

    Sprite* imagem = new Sprite(associated, file);
    imagem->SetScaleX(escala.x, escala.y);

    associated.AddComponent(imagem);

// ajusta a box de colisao para o tamanho determinado pela imagem//

    Collider* colisor = new Collider(associated);

    float offx = (-1) *((escala.x - 1)*(imagem->GetWidth()/escala.x)/2);
    float offy = (-1) *((escala.y - 1)*(imagem->GetHeight()/escala.y)/2);

    colisor->SetOffset(Vec2(offx,offy));
    colisor->SetScale(escala);
    this->associated.AddComponent(colisor);

    this->colisor = colisor;

// identifica do que sera feito o bloco//
    this->tipo = tipo;




}


Bloco :: ~Bloco(){}


void Bloco :: Start(){

// inicia o checkpoint com a imagem de checkpoint atual
    if(this->tipo == "checkpoint"){
        if(this->associated.box.x == GameData::checkPointX){
            Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

            if(jog!= nullptr){
                jog->setTexture("./assets/img/camp_salvo.png");
            }

        }
    }
}



void Bloco :: Update(float dt){

// transforma todos os checkpoints n ativos atualmente com a imagem de nao ativo
    if(this->tipo == "checkpoint"){
        if(this->associated.box.x != GameData::checkPointX){
            Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

            if(jog!= nullptr){
                jog->setTexture("./assets/img/camp_aceso.png");
            }

        }
    }

}



void Bloco :: Render(){}
        
        
bool Bloco :: Is(std::string type){

    if (type == "Bloco"){
        return true;
    };
    return false;

}
   
   
   
void Bloco :: NotifyCollision ( GameObject& other){

    Jogador *player =  (Jogador*)other.GetComponent("Jogador");

// se o bloco for do tipo 'checkpoint', se o jogador apertar x ele muda o sprite //

    if(player != nullptr){

        if(this->tipo == "checkpoint"){

            if(InputManager :: GetInstance().KeyPress(SDLK_x)){

                Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

                if(jog!= nullptr){
                        jog->setTexture("./assets/img/camp_salvo.png");
                }

            }

        }


    if(this->tipo == "mascara"){

            if(InputManager :: GetInstance().KeyPress(SDLK_q)){

                GameData::item = 1;
                GameObject* morte = new GameObject();

                morte->box = associated.box;

                associated.RequestDelete(); 

            }

        }
            if(this->tipo == "garra"){

            if(InputManager :: GetInstance().KeyPress(SDLK_q)){

                GameData::garra = 1;
                GameObject* morte1 = new GameObject();

                morte1->box = associated.box;

                associated.RequestDelete(); 

            }

        }    

    }

}



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

// ve se o vetor passado esta dentro do bloco //

    return colisor->box.Contains(vetor);


}




std::string Bloco:: getTipo(){

// retorna o tipo do bloco //

    return tipo;


}