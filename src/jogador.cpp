#include "../include/jogador.h"
#include "../include/sprite.h"
#include "../include/state.h"
#include "../include/game.h"
#include "../include/inputmanager.h"
#include "../include/collider.h"
#include "../include/bullet.h"
#include "../include/camera.h"
#include "../include/alien.h"
#include "../include/minion.h"


Jogador* Jogador::player = nullptr;

Jogador :: Jogador(GameObject& associated) : Component(associated){



    hp = 5;
    angle = 0;
    atrito = 1;
    speed = Vec2(0,0);

    player = this;

    
    gravidade = 2;
    gravidadeMax = 80;
    velPulo = -30;

    numJumps = 1;
    pulosRestantes = numJumps;

    encostar = new Timer();
    invuneravel = new Timer();
    contato = 0;

    caindo = false;
    parado = false;
    agarrado = false;

    checkpoint.x = associated.box.x;
    checkpoint.y = associated.box.y;


}

Jogador :: ~Jogador(){

    player = nullptr;


}



void Jogador :: Start(){}



void Jogador :: Update (float dt){


    posyh_anterior = associated.box.y + associated.box.h;
    posy_anterior = associated.box.y;

    int velocidade = 50;

/*
    encostar->Update(dt);

    if(contato == 1){

        invuneravel->Update(dt);
        Sprite* peng = (Sprite*)associated.GetComponent("sprite");


        if((encostar->Get() < 1) and (invuneravel->Get() > 0.1)){

            if(peng != nullptr){
                peng->setPiscar();
            }
            invuneravel->Restart();
        }
        else if(encostar->Get() > 1){
            contato = 0;
            peng->setOriginal();
        }

    }

*/

    if (caindo){

        if(agarrado){
           if(speed.y < 1){
                speed.y = speed.y + 1;
            }
            else{
                speed.y = 5;
            }

        }
        else{
            if(speed.y < gravidadeMax){
                speed.y = speed.y + gravidade;
            }
            else{
                speed.y = gravidadeMax;
            }
        }
    }




    Vec2 atual = Vec2(associated.box.x, associated.box.y);



    if((InputManager :: GetInstance().KeyPress(SDLK_SPACE)) and (pulosRestantes > 0)){

        pulosRestantes = pulosRestantes - 1;


        speed.y = velPulo;

    }

    if((InputManager :: GetInstance().KeyPress(SDLK_SPACE)) and (agarrado)){

        speed.y = velPulo;
        if(ladoGrudado == 1){
            speed.x = 20;
        }
        else if (ladoGrudado == 2){
            speed.x = -20;
        }

    }

    if(InputManager :: GetInstance().IsKeyDown(SDLK_d)){

        parado = false;
        Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

        if(jog!= nullptr){
            jog->setTexture("./assets/img/sonic.png");
            jog->SetFrameCount(1);
            jog->SetFrameTime(0);        
        }


        if(speed.x < velocidade){
            speed.x = speed.x + 1;
        }
        else{
            speed.x = velocidade;
        }

    }
    else if(InputManager :: GetInstance().IsKeyDown(SDLK_a)){

        parado = false;
        Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

        if(jog!= nullptr){
            jog->setTexture("./assets/img/sonic2.png");
            jog->SetFrameCount(1);
            jog->SetFrameTime(0);
        }        

        if(speed.x > -velocidade){
            speed.x = speed.x - 1;
        }
        else{
            speed.x = -velocidade;
        }

    }
    else{
        if(speed.x > 0){
            speed.x = speed.x - atrito;
        }
        else if (speed.x < 0){
            speed.x = speed.x + atrito;
        }
        else{
            speed.x = 0;
        }

    }



    if((speed.x == 0) and (parado == false)){

        parado = true;
        Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

        if(jog!= nullptr){

            jog->setTexture("./assets/img/ss.png");
            jog->SetFrameCount(4);
            jog->SetFrameTime(0.4);


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


        Camera::Unfollow();

        Sprite* explosao = new Sprite(*morte, "./assets/img/penguindeath.png" , 5, 0.2, 1);

        morte->AddComponent(explosao);

        State& temp = Game::GetInstance().GetCurrentState();

        Sound* som = new Sound(*morte, "./assets/audio/boom.wav");

        som->Play();



        morte->AddComponent(som);

        temp.AddObject(morte);



    }

    caindo = true;
    agarrado = false;

}





void Jogador :: Render (){}



bool Jogador :: Is(std::string type){


    if (type == "Jogador"){
        return true;
    };
    return false;



}






void Jogador :: NotifyCollision ( GameObject& other){


    Bloco *chao =  (Bloco*)other.GetComponent("Bloco");


    if(chao != nullptr){
        movimentacaoTipoChao(chao);
    }


}



Rect Jogador :: GetPos(){

    return associated.box;

}



void Jogador :: movimentacaoTipoChao(Bloco *chao){


    if(chao->getTipo() == "terra"){


        if((chao->Contains(Vec2(associated.box.x, associated.box.y)) and (chao->Contains(Vec2(associated.box.x + associated.box.w, associated.box.y))))){

            associated.box.y = chao->getY() + chao->getHigh();
            speed.y = 0;
            

        }

        else if((chao->Contains(Vec2(associated.box.x, associated.box.y)) and (chao->Contains(Vec2(associated.box.x, associated.box.y + associated.box.h))))){

            associated.box.x = chao->getX() + chao->getLength();
            agarrado = true;
            ladoGrudado = 1;
            speed.x = 0;

        }
        
        else if((chao->Contains(Vec2(associated.box.x + associated.box.w, associated.box.y)) and (chao->Contains(Vec2(associated.box.x + associated.box.w, associated.box.y + associated.box.h))))){

            associated.box.x = chao->getX() - 48;
            agarrado = true;
            ladoGrudado = 2;
            speed.x = 0;

        }

        else if((chao->Contains(Vec2(associated.box.x, associated.box.y + associated.box.h)) and (chao->Contains(Vec2(associated.box.x + associated.box.w, associated.box.y + associated.box.h))))){

            associated.box.y = chao->getY() - 57;
            caindo = false;
            pulosRestantes = numJumps;
            speed.y = 0;

        }

        




        else if((chao->Contains(Vec2(associated.box.x + associated.box.w, associated.box.y + associated.box.h)))){
          
            if(speed.y < 0){

                associated.box.x = chao->getX() - 48;
                agarrado = true;
                ladoGrudado = 2;
                speed.x = 0;

            }
            else{

                if(posyh_anterior > chao->getY()){

                    associated.box.x = chao->getX() - 48;
                    agarrado = true;
                    ladoGrudado = 2;
                    speed.x = 0;                    
                
                }
                else{
                    associated.box.y = chao->getY() - 57;
                    caindo = false;
                    pulosRestantes = numJumps;
                    speed.y = 0;
                }
            }

        }

        else if((chao->Contains(Vec2(associated.box.x, associated.box.y + associated.box.h)))){

            
            if(speed.y < 0){
            
                associated.box.x = chao->getX() + chao->getLength();
                agarrado = true;
                ladoGrudado = 1;
                speed.x = 0;

            }
            else{
                if(posyh_anterior > chao->getY()){

                    associated.box.x = chao->getX() + chao->getLength();
                    agarrado = true;
                    ladoGrudado = 1;
                    speed.x = 0;                  
                
                }
                else{
                    associated.box.y = chao->getY() - 57;
                    pulosRestantes = numJumps;
                    caindo = false;
                    speed.y = 0;
                }

            }
        }

        else if((chao->Contains(Vec2(associated.box.x, associated.box.y)))){

            
            if(speed.y > 0){
            
                associated.box.x = chao->getX() + chao->getLength();
                agarrado = true;
                ladoGrudado = 1;
                speed.x = 0;

            }
            else{

                if(posy_anterior < chao->getY() + chao->getHigh()){

                    associated.box.x = chao->getX() + chao->getLength();
                    agarrado = true;
                    ladoGrudado = 1;
                    speed.x = 0;                 
                
                }
                else{
                    associated.box.y = chao->getY() + chao->getHigh();
                    speed.y = 0;
                }

            }
        }

        else if((chao->Contains(Vec2(associated.box.x + associated.box.w, associated.box.y)))){

            
            if(speed.y >0){
            
                associated.box.x = chao->getX() -48;
                agarrado = true;
                ladoGrudado = 2;
                speed.x = 0;

            }
            else{
                if(posy_anterior < chao->getY() + chao->getHigh()){

                    associated.box.x = chao->getX() -48;
                    agarrado = true;
                    ladoGrudado = 2;
                    speed.x = 0;             
                
                }
                else{
                    associated.box.y = chao->getY() + chao->getHigh();
                    speed.y = 0;
                }

            }
        }
    }


    if(chao->getTipo() == "lava"){

        hp = hp - 1;
        associated.box.x = checkpoint.x;
        associated.box.y = checkpoint.y;

    }
}