#include "../include/penguinbody.h"
#include "../include/sprite.h"
#include "../include/state.h"
#include "../include/penguincannon.h"
#include "../include/game.h"
#include "../include/inputmanager.h"
#include "../include/collider.h"
#include "../include/bullet.h"
#include "../include/camera.h"
#include "../include/alien.h"
#include "../include/minion.h"
#include "../include/bloco.h"

PenguinBody* PenguinBody::player = nullptr;

PenguinBody :: PenguinBody(GameObject& associated) : Component(associated){



    hp = 5;
    angle = 0;
    linearSpeed = 1;
    speed = Vec2(0,0);

    player = this;

    


    Sprite* peng = new Sprite(associated,"./assets/img/penguin.png" );

    associated.AddComponent(peng);

    Collider* colisor = new Collider(associated);
    this->associated.AddComponent(colisor);
    encostar = new Timer();
    invuneravel = new Timer();
    aconteceu = 0;

    caindo = false;


}

PenguinBody :: ~PenguinBody(){

    player = nullptr;


}



void PenguinBody :: Start(){

    State& temp = Game::GetInstance().GetCurrentState();

    GameObject* objeto = new GameObject();


    std::weak_ptr< GameObject > peng = temp.GetObjectPtr(&associated);


    PenguinCannon* canhao = new PenguinCannon(*objeto, peng);

    objeto->AddComponent(canhao);

    pcannon = temp.AddObject(objeto);




}



void PenguinBody :: Update (float dt){

    int velocidade = 50;

    encostar->Update(dt);

    if(aconteceu == 1){

        invuneravel->Update(dt);
        Sprite* peng = (Sprite*)associated.GetComponent("sprite");
        Sprite* canhao = (Sprite*)pcannon.lock()->GetComponent("sprite");


        if((encostar->Get() < 1) and (invuneravel->Get() > 0.1)){

            if(peng != nullptr){
                peng->setPiscar();
            }
            if(canhao!=nullptr){
                canhao->setPiscar();
            }
            invuneravel->Restart();
        }
        else if(encostar->Get() > 1){
            aconteceu = 0;
            peng->setOriginal();
            canhao->setOriginal();
        }

    }

    if (caindo){

        speed.y = speed.y + 2;


    }




    Vec2 atual = Vec2(associated.box.x, associated.box.y);



    if(InputManager :: GetInstance().KeyPress(SDLK_SPACE)){
        

            speed.y = -30;

    }

    if(InputManager :: GetInstance().IsKeyDown(SDLK_d)){
        
        if(speed.x < velocidade){
            speed.x = speed.x + 1;
        }
        else{
            speed.x = velocidade;
        }
        if(angle != 2*M_PI/60){
            angle = 2*M_PI/60;
            associated.angleDeg = angle;
        } 
    }
    else if(InputManager :: GetInstance().IsKeyDown(SDLK_a)){

        if(speed.x > -velocidade){
            speed.x = speed.x - 1;
        }
        else{
            speed.x = -velocidade;
        }
        if(angle != 0){
            angle = 0;
            associated.angleDeg = angle;
        }
    }
    else{
        if(speed.x > 0){
            speed.x = speed.x - linearSpeed;
        }
        else if (speed.x < 0){
            speed.x = speed.x + linearSpeed;
        }
        else{
            speed.x = 0;
        }

    }






    Vec2 temp;

    temp.x = speed.x * dt * 10;
    temp.y = speed.y * dt * 10;

    atual.x = atual.x + temp.x;
    atual.y = atual.y + temp.y;


    associated.box.x = atual.x;
    associated.box.y = atual.y;



    if(hp <=0 ){

        GameObject* morte = new GameObject();

        morte->box = associated.box;

        associated.RequestDelete();
        pcannon.lock()->RequestDelete();


        Camera::Unfollow();

        Sprite* explosao = new Sprite(*morte, "./assets/img/penguindeath.png" , 5, 0.2, 1);

        morte->AddComponent(explosao);

        State& temp = Game::GetInstance().GetCurrentState();

        Sound* som = new Sound(*morte, "./assets/audio/boom.wav");

        som->Play();



        morte->AddComponent(som);

        temp.AddObject(morte);



    }


}





void PenguinBody :: Render (){}



bool PenguinBody :: Is(std::string type){


    if (type == "penguinbody"){
        return true;
    };
    return false;



}






void PenguinBody :: NotifyCollision ( GameObject& other){

    /*
    Bullet *tiro = (Bullet *)other.GetComponent("Bullet");

    if(tiro != nullptr){

        if(tiro->targetsPlayer == true){

            int dano = tiro->GetDamage();

            other.RequestDelete();


            if (encostar->Get() > 1){
                hp = hp - dano;
                aconteceu = 1;
                encostar->Restart();
            }

        }

    }

    Alien *inimigo = (Alien*)other.GetComponent("Alien");


    if(inimigo != nullptr){
        
        if(encostar->Get() > 1){

            hp = hp - 1;
            aconteceu = 1;
            encostar->Restart();
        }
    }

    Minion *minio = (Minion*)other.GetComponent("Minion");

    if(minio != nullptr){

        if(encostar->Get() > 1){
            hp = hp - 1;
            aconteceu = 1;
            encostar->Restart();

        }

    }
    */


    Bloco *chao =  (Bloco*)other.GetComponent("Bloco");


    if(chao != nullptr){

        Vec2 meio = chao->getcenter();

        if((associated.box.y + 57 >= chao->getY()) and (associated.box.y + 57 < meio.y)){
            associated.box.y = chao->getY() - 57;
            speed.y = 0;
            caindo = false;
        }

        if((associated.box.y <= chao->getY() + chao->getHigh()) and (associated.box.y >= meio.y)){
            associated.box.y = chao->getY() + chao->getHigh();
            speed.y = 0;
        }

    }
    else{

        caindo = true;

    }

}



Rect PenguinBody :: GetPos(){

    return associated.box;

}