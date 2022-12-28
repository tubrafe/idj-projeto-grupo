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


    Sprite* personagem = new Sprite(associated,"./assets/img/pers_parado1.png" );
    associated.AddComponent(personagem);
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

    // controla caso o jogador incoste em um inimigo e caso encoste o tempo de invunerabilidade dele
    encostar = new Timer();
    invuneravel = new Timer();
    contato = 0;

    // estado do jogador, sendo andandod de andando para direita, e andandoe andando para a esquerda
    caindo = false;
    parado = false;
    agarrado = false;
    andandod = false;
    andandoe = false;

    //controla o ponto de nascimento do jogador
    checkpoint.x = associated.box.x;
    checkpoint.y = associated.box.y;

    // pega o tamanho do sprite atual do jogador
    Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

    if(jog!= nullptr){
        largura = jog->GetWidth();
        altura = jog->GetHeight();       
    }

}



Jogador :: ~Jogador(){

    player = nullptr;


}



void Jogador :: Start(){}



void Jogador :: Update (float dt){

    //grava a posicao anterior do jogador para o calculo de impacto com o solo mostrado mais a frente
    posyh_anterior = associated.box.y + associated.box.h;
    posy_anterior = associated.box.y;

    int velocidade = 50;

// isso eh usado para caso o jogador encoste em um inimigo, por isso n esta sendo usado no momento

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

// se o jogador estiver caindo, calcula a velocidade da queda, dependendo se estiver agarrado a parede ou n
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



    // posicao inicial do jogador antes da atualizacao de movimento
    Vec2 atual = Vec2(associated.box.x, associated.box.y);


    // se o jogador apertar espaco ele pula se tiver pulo disponivel (caso como por exemplo ele ter double jump)
    if((InputManager :: GetInstance().KeyPress(SDLK_SPACE)) and (pulosRestantes > 0)){

        pulosRestantes = pulosRestantes - 1;


        speed.y = velPulo;

    }

    // pulo diferenciado para caso ele pule a partir de uma parede, sendo o valor 1 se ele estiver agarrado a uma parede pela
    // direita dela, ou 2 se for pela esquerda
    if((InputManager :: GetInstance().KeyPress(SDLK_SPACE)) and (agarrado)){

        speed.y = velPulo;
        if(ladoGrudado == 1){
            speed.x = 10;
        }
        else if (ladoGrudado == 2){
            speed.x = -10;
        }

    }

    // movimento para a direita
    if(InputManager :: GetInstance().IsKeyDown(SDLK_d)){

        parado = false;
        andandoe = false;
        // seta o sprite dele andando para a direita apenas uma vez enquanto isso se repetir
        if(andandod == false){
            Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

            if(jog!= nullptr){
                jog->setTexture("./assets/img/pers_andando1.png");
                jog->SetFrameCount(5);
                jog->SetFrameTime(0.2);      
            }
        }
        andandod = true;
        if(speed.x < velocidade){
            speed.x = speed.x + 1;
        }
        else{
            speed.x = velocidade;
        }

    }
    // movimento para a esquerda
    else if(InputManager :: GetInstance().IsKeyDown(SDLK_a)){

        parado = false;
        andandod = false;
        // seta o sprite dele andando para a esquerda apenas uma vez enquanto isso se repetir
        if(andandoe == false){
            Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

            if(jog!= nullptr){
                jog->setTexture("./assets/img/pers_andando2.png");
                jog->SetFrameCount(5);
                jog->SetFrameTime(0.2); 
            }        
        }
        andandoe = true;        
        if(speed.x > -velocidade){
            speed.x = speed.x - 1;
        }
        else{
            speed.x = -velocidade;
        }

    }
    // caso ele pare de segurar alguma das teclas a e d, ele vai perdendo velocidade ate parar
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


    // caso ele esteja parado, seta o sprite dele parado dependendo de qual direcao ele tava andando
    if((speed.x == 0) and (parado == false)){

        parado = true;
        Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

        if(jog!= nullptr){

            if(andandod == true){
                jog->setTexture("./assets/img/pers_parado1.png");
                jog->SetFrameCount(1);
                jog->SetFrameTime(0);
            }
            if(andandoe == true){
                jog->setTexture("./assets/img/pers_parado2.png");
                jog->SetFrameCount(1);
                jog->SetFrameTime(0);
            }

        }
        andandod = false;
        andandoe = false;
    }

    // atualiza o tamanho da imagem do jogador caso tenha mudado
    Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

    if(jog!= nullptr){
        largura = jog->GetWidth();
        altura = jog->GetHeight();       
    }


    // atualiza a posicao do jogador
    Vec2 temp;

    temp.x = speed.x * dt * 10;
    temp.y = speed.y * dt * 10;

    atual.x = atual.x + temp.x;
    atual.y = atual.y + temp.y;


    associated.box.x = atual.x;
    associated.box.y = atual.y;


    // caso o jogador morra
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

    //refaz essas variaveis para o calculo de impacto com o solo
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

    // caso ele colida com um objeto de um tipo bloco, ele vai para essa funcao
    // para decidir o que sera feito dependendo do tipo colidido
    if(chao != nullptr){
        movimentacaoTipoChao(chao);
    }


}



Rect Jogador :: GetPos(){

    return associated.box;

}


// funcao para decidir o que sera feito com colisoes do tipo bloco
void Jogador :: movimentacaoTipoChao(Bloco *chao){

    // caso colida com o chao comum
    if(chao->getTipo() == "terra"){

        /*
        calculo para teleportar o jogador para um dos 4 lados do retangulo no caso de colisao para dar a impreensao de que esta colidindo
        os primeiros 4 ifs, verifica se 2 vertices consecutivos da box do jogador esta colidindo com o bloco, considerando que os vertices sao
        x,y: vertice esquerdo superior/ x,y+h: vertice esquerdo inferior/ x+w,y: vertice direito superior/ x+w,y+h: vertice direito inferior
        caso os dois vertices de cima estejam colidindo, eh o caso que a cabeca do personagem ta encostando o bloco, ou seja ele esta embaixo dele
        caso os dois vertices de baixo estejam colidindo, eh o caso que os pes do personagem ta encostando o bloco, ou seja ele esta emcima dele
        caso os dois vertices da direita estejam colidindo, eh o caso dele esta colidindo com a esquerda do bloco e
        caso os dois vertices da esquerda estejam colidindo, eh o caso dele esta colidindo com a direita do bloco
        */

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

            associated.box.x = chao->getX() - largura;
            agarrado = true;
            ladoGrudado = 2;
            speed.x = 0;

        }

        else if((chao->Contains(Vec2(associated.box.x, associated.box.y + associated.box.h)) and (chao->Contains(Vec2(associated.box.x + associated.box.w, associated.box.y + associated.box.h))))){

            associated.box.y = chao->getY() - altura;
            caindo = false;
            pulosRestantes = numJumps;
            speed.y = 0;

        }

        /*      
        os proximos ifs, sao quando apenas um vertice esta encostando no bloco, ou seja nos cantos do retangulo do chao
        para isso alem dos vertices eh necessario saber a posicao anterior antes da colisao do personagem, pois tera os seguintes casos
        caso algum vertice de cima esta colidindo, deve ser necessario saber se o jogador sera teleportado para o lado ou para baixo, para isso
        eh feito um calculo assim: se o y anterior dele esta mais baixo que o bloco, eh pq ele esta batendo com a cabeca logo ele eh teleportado
        para baixo, caso ele fosse mais alto eh pq ele esta batendo nos lados do bloco, e com isso ele eh teleportado para a posicao certa, o mesmo vale
        para os vertices de baixo
        */


        else if((chao->Contains(Vec2(associated.box.x + associated.box.w, associated.box.y + associated.box.h)))){
          
            if(speed.y < 0){

                associated.box.x = chao->getX() - largura;
                agarrado = true;
                ladoGrudado = 2;
                speed.x = 0;

            }
            else{

                if(posyh_anterior > chao->getY()){

                    associated.box.x = chao->getX() - largura;
                    agarrado = true;
                    ladoGrudado = 2;
                    speed.x = 0;                    
                
                }
                else{
                    associated.box.y = chao->getY() - altura;
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
                    associated.box.y = chao->getY() - altura;
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
            
                associated.box.x = chao->getX() -largura;
                agarrado = true;
                ladoGrudado = 2;
                speed.x = 0;

            }
            else{
                if(posy_anterior < chao->getY() + chao->getHigh()){

                    associated.box.x = chao->getX() -largura;
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

    // caso seja um tipo de bloco de perigo o personagem perde uma vida
    // e volta ao checkpoint
    if(chao->getTipo() == "lava"){

        hp = hp - 1;
        associated.box.x = checkpoint.x;
        associated.box.y = checkpoint.y;
        speed.x = 0;
        speed.y = 0;

    }
    // caso seja de um tipo checkpoint e o jogador apertar x
    // o checkpoint do jogador eh atualizado para a posicao do bloco
      if(chao->getTipo() == "checkpoint"){

        if(InputManager :: GetInstance().KeyPress(SDLK_x)){
            checkpoint.x = chao->getX();
            checkpoint.y = chao->getY();
        }

    }  
}