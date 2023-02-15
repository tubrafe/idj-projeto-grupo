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
#include "../include/gamedata.h"


Jogador* Jogador::player = nullptr;

//vida e stamina passao a ser variaveis globais de todos os modulos ao inves de apenas o jogador
Jogador :: Jogador(GameObject& associated, Hud* hud) : Component(associated){


    Sprite* personagem = new Sprite(associated,"./assets/img/pers_parado1.png" );
    associated.AddComponent(personagem);
    if(GameData::hp_atual <= 0){
        GameData::hp_atual = GameData::hp_total;
    }
    angle = 0;
    atrito = 1;
    speed = Vec2(0,0);

    player = this;


    cd_stamina = new Timer();
    
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
    dash = false;
    anima_grudado = false;
    damaged = false;
    caiu = false;
    anima_dash = false;

    // guarda o ultimo lado pra o qual o personagem ta virado para usar o dash
    ladoVirado = true;

    dash_cd = new Timer();

    // serve para o controle das animacoes quando ocorre um pulo
    anima_caindo = false;
    speed_anterior = 1;

    //sons
    sons = new Sound(associated, "./assets/audio/boom.wav");

    // pega o tamanho do sprite atual do jogador
    Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

    if(jog!= nullptr){
        largura = jog->GetWidth();
        altura = jog->GetHeight();       
    }



    barra_vida = hud;


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

// controle da stamina que o jogador possui no momento
    cd_stamina->Update(dt);

    if(cd_stamina->Get() > 0.5){

        cd_stamina->Restart();

        if(agarrado){
            GameData::stamina_atual = GameData::stamina_atual - 1;

            if(GameData::stamina_atual  < 0){
                GameData::stamina_atual  = 0;
            }

        }
        else{
            GameData::stamina_atual  = GameData::stamina_atual  + 0.5;
            if(GameData::stamina_atual  > GameData::stamina_total){
                GameData::stamina_atual  = GameData::stamina_total ;
            }
        }

    }


    if(!damaged){

        invuneravel->Restart();

    }
    else{
        invuneravel->Update(dt);
        if(invuneravel->Get() > 0.2){
            damaged = false;
        }

    }

    if(!caiu){
        encostar->Restart();
    }
    else{
        encostar->Update(dt);
        if(encostar->Get() > 0.2){
            caiu = false;
        }

    }
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

        if((agarrado) and (GameData::stamina_atual > 0)){

            Sprite *jog =  (Sprite*)associated.GetComponent("sprite");
            if(anima_grudado == false){
                if(jog!= nullptr){
                    if(ladoGrudado == 1){
                        jog->setTexture("./assets/img/grudado.png");
                        jog->SetFrameCount(4);
                        jog->SetFrameTime(0.2);
                    } 
                    else{
                        jog->setTexture("./assets/img/grudado2.png");
                        jog->SetFrameCount(4);
                        jog->SetFrameTime(0.2);                        
                    }
                } 
                sons->Stop();
                anima_grudado = true;
            }

           if(speed.y < 1){
                speed.y = speed.y + 1;
            }
            else{
                speed.y = 5;
            }

        }
        else{
            anima_grudado = false;

            if(speed.y < gravidadeMax){
                speed.y = speed.y + gravidade;
            }
            else{
                speed.y = gravidadeMax;
            }
        }
    }

    // serve para colocar a animacao do personagem caindo
    if((caindo) and  (!agarrado)){

        if((speed.y >= 0)){

            Sprite *jog =  (Sprite*)associated.GetComponent("sprite");
            if(((anima_caindo == false) or (InputManager :: GetInstance().IsKeyDown(SDLK_a)) or (InputManager :: GetInstance().IsKeyDown(SDLK_d))) and (!dash)){
                if(jog!= nullptr){
                    if(ladoVirado){
                        jog->setTexture("./assets/img/parado_ar.png");
                        jog->SetFrameCount(2);
                        jog->SetFrameTime(0.2);
                    }
                    else{
                         jog->setTexture("./assets/img/parado_ar2.png");
                        jog->SetFrameCount(2);
                        jog->SetFrameTime(0.2);                       
                    }

                } 
                if((!dash) and (!damaged) and (!caiu)){
                    sons->Stop();
                }
                anima_caindo = true;
            }
            parado = false;
            andandod = false;
            andandoe = false;
    
        }



        }

    // caso ele esteja parado, seta o sprite dele parado dependendo de qual direcao ele tava andando
    if((speed.x == 0) and (parado == false)){

        parado = true;
        Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

        if(jog!= nullptr){

            if((andandod == true) and (!dash)){
                jog->setTexture("./assets/img/pers_parado1.png");
                jog->SetFrameCount(1);
                jog->SetFrameTime(0);
                if((!dash) and (!damaged) and (!caiu)){
                    sons->Stop();
                }
                andandod = false;
                andandoe = false;
                anima_caindo = false;
                ladoVirado = true;
                anima_grudado = false;
            }
            else if((andandoe == true) and (!dash)){
                jog->setTexture("./assets/img/pers_parado2.png");
                jog->SetFrameCount(1);
                jog->SetFrameTime(0);
                if((!dash) and (!damaged) and (!caiu)){
                    sons->Stop();
                }
                andandod = false;
                andandoe = false;
                anima_caindo = false;
                ladoVirado = false;
                anima_grudado = false;
            }

            // esses dois casos servem para quando o jogador pular e parar de se movimentar, para que o sprite esteja correto dele parado
            else if((speed_anterior == 1) and (!caindo) and (!dash)){
                jog->setTexture("./assets/img/pers_parado1.png");
                jog->SetFrameCount(1);
                jog->SetFrameTime(0);
                if((!dash) and (!damaged) and (!caiu)){
                    sons->Stop();
                }
                andandod = false;
                andandoe = false;
                anima_caindo = false;
                ladoVirado = true;
                anima_grudado = false;
            }
            else if((speed_anterior == -1) and (!caindo) and (!dash)){
                jog->setTexture("./assets/img/pers_parado2.png");
                jog->SetFrameCount(1);
                jog->SetFrameTime(0);
                if((!dash) and (!damaged) and (!caiu)){
                    sons->Stop();
                }
                andandod = false;
                andandoe = false;
                anima_caindo = false;
                ladoVirado = false;
                anima_grudado = false;
            }
        }

    }

    // posicao inicial do jogador antes da atualizacao de movimento
    Vec2 atual = Vec2(associated.box.x, associated.box.y);


    // se o jogador apertar espaco ele pula se tiver pulo disponivel (caso como por exemplo ele ter double jump)
    // alem de colocar a animacao do pulo
    if((InputManager :: GetInstance().KeyPress(SDLK_SPACE)) and (pulosRestantes > 0)){

        pulosRestantes = pulosRestantes - 1;
        pulando = true;
        Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

            if(jog!= nullptr){
                if(ladoVirado == true){
                    jog->setTexture("./assets/img/subida.png");
                }
                else{
                    jog->setTexture("./assets/img/subida2.png");
                }
                sons->Stop();
                sons->setSound("./assets/audio/pulo.wav");
                sons->Play();
                jog->SetFrameCount(3);
                jog->SetFrameTime(0.2); 
            }        
        
        parado = false;
        andandod = false;
        andandoe = false;
        anima_caindo = false;
        anima_grudado = false;
        speed.y = velPulo;

    }

    // pulo diferenciado para caso ele pule a partir de uma parede, sendo o valor 1 se ele estiver agarrado a uma parede pela
    // direita dela, ou 2 se for pela esquerda
    if((InputManager :: GetInstance().KeyPress(SDLK_SPACE)) and (agarrado) and (GameData::stamina_atual>0)){

        speed.y = velPulo;
        Sprite *jog =  (Sprite*)associated.GetComponent("sprite");
        pulando = true;
        if(jog!= nullptr){
            if(ladoVirado == true){
                jog->setTexture("./assets/img/subida.png");
            }
            else{
                jog->setTexture("./assets/img/subida2.png");
            }
            sons->Stop();
            jog->SetFrameCount(3);
            jog->SetFrameTime(0.2); 
        }
        if(ladoGrudado == 1){
            speed.x = 10;
        }
        else if (ladoGrudado == 2){
            speed.x = -10;
        }

    }


//ativa o dash
    if((InputManager :: GetInstance().KeyPress(SDLK_z)) and (GameData::stamina_atual>2.5) and (dash == false)){

        dash = true;
        GameData::stamina_atual = GameData::stamina_atual - 2.5;
        sons->Stop();
        sons->setSound("./assets/audio/dash.wav");
        sons->Play();
        dash_cd->Restart();

    }


    // movimento para a direita
    if(InputManager :: GetInstance().IsKeyDown(SDLK_d)){


        // seta o sprite dele andando para a direita apenas uma vez enquanto isso se repetir
        if((andandod == false) and (caindo == false) and (pulando == false) and (!dash)){
            
            Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

            if(jog!= nullptr){
                jog->setTexture("./assets/img/pers_andando1.png");
                jog->SetFrameCount(5);
                jog->SetFrameTime(0.2); 

            }

                sons->Stop();
                sons->setSound("./assets/audio/passos.wav");
                sons->Play();


            andandod = true;
            anima_caindo = false;
            parado = false;
            andandoe = false;

            anima_grudado = false;
        }
            ladoVirado = true;
        if(speed.x < velocidade){
            speed.x = speed.x + 1;
        }
        else{
            speed.x = velocidade;
        }

    }
    // movimento para a esquerda
    else if(InputManager :: GetInstance().IsKeyDown(SDLK_a)){
        

        // seta o sprite dele andando para a esquerda apenas uma vez enquanto isso se repetir
        if((andandoe == false) and (caindo == false) and (pulando == false) and (!dash)){
            Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

            if(jog!= nullptr){
                jog->setTexture("./assets/img/pers_andando2.png");
                jog->SetFrameCount(5);
                jog->SetFrameTime(0.2); 
            }  

                sons->Stop();
                sons->setSound("./assets/audio/passos.wav");
                sons->Play(); 



            andandoe = true;   
            anima_caindo = false;
            parado = false;
            andandod = false;
 
            anima_grudado = false;    
        }
            ladoVirado = false;
        if(speed.x > -velocidade){
            speed.x = speed.x - 1;
        }
        else{
            speed.x = -velocidade;
        }

    }
    // caso ele pare de segurar alguma das teclas a e d, ele vai perdendo velocidade ate parar
    // adicionado dois casos, para q caso o personagem caia mas continue em movimento sem o jogador precionar alguma tecla
    // para que a animacao mude para o personagem andando
    else{
        if(speed.x > 0){
            speed.x = speed.x - atrito;
            speed_anterior = 1;

            if((!caindo) and (!andandod) and (!pulando) and (!dash)){
                Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

                if(jog!= nullptr){
                    jog->setTexture("./assets/img/pers_andando1.png");
                    jog->SetFrameCount(5);
                    jog->SetFrameTime(0.2);      
                }

                sons->Stop();
                sons->setSound("./assets/audio/passos.wav");
                sons->Play();

            
                andandod = true;
                anima_caindo = false;
                parado = false;
                andandoe = false;
                ladoVirado = true;
                anima_grudado = false;
            }
        }
        else if (speed.x < 0){
            speed.x = speed.x + atrito;
            speed_anterior = -1;

            if((!caindo) and (!andandoe) and (!pulando) and (!dash)){
                Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

                if(jog!= nullptr){
                    jog->setTexture("./assets/img/pers_andando2.png");
                    jog->SetFrameCount(5);
                    jog->SetFrameTime(0.2); 
                }  

                sons->Stop();
                sons->setSound("./assets/audio/passos.wav");
                sons->Play();


                andandoe = true;   
                anima_caindo = false;
                parado = false;
                andandod = false; 
                ladoVirado = false;  
                anima_grudado = false;  
            }
        }
        else{
            speed.x = 0;
        }

    }




    // atualiza o tamanho da imagem do jogador caso tenha mudado
    Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

    if(jog!= nullptr){
        largura = jog->GetWidth();
        altura = jog->GetHeight();       
    }
//atualiza a velocidade para ela ser bem grande durante o dash
    if(dash == true){
        
        if(anima_dash == false){
            anima_dash = true;
            Sprite *jog =  (Sprite*)associated.GetComponent("sprite");

            if(ladoVirado == true){
                if(jog!= nullptr){
                    jog->setTexture("./assets/img/dash.png");
                    jog->SetFrameCount(1);
                    jog->SetFrameTime(0.2);     
                } 
            }  
            else{
                if(jog!= nullptr){
                    jog->setTexture("./assets/img/dash2.png");
                    jog->SetFrameCount(1);
                    jog->SetFrameTime(0.2);     
                } 

            }    
        }

        if(dash_cd->Get()<0.2){
            if(ladoVirado == true){
                speed.x = 100;
            }
            else{
                speed.x = -100;
            }
        }
        else{
            anima_dash = false;
            dash = false;
            speed.x = 0;
        }
        dash_cd->Update(dt);
    }

    // atualiza a posicao do jogador
    Vec2 temp;

    temp.x = speed.x * dt * 10;
    temp.y = speed.y * dt * 10;

    atual.x = atual.x + temp.x;
    atual.y = atual.y + temp.y;


    associated.box.x = atual.x;
    associated.box.y = atual.y;


	barra_vida->SetPos(Vec2(associated.box.x-15, associated.box.y-80));

    if(GameData::hp_atual == 5){
	    barra_vida->SetTexture("./assets/img/vida_5.png");
    }
    else if(GameData::hp_atual == 4){
	    barra_vida->SetTexture("./assets/img/vida_4.png");
    }
    else if(GameData::hp_atual == 3){
	    barra_vida->SetTexture("./assets/img/vida_3.png");
    }
    else if(GameData::hp_atual == 2){
	    barra_vida->SetTexture("./assets/img/vida_2.png");
    }
    else{
	    barra_vida->SetTexture("./assets/img/vida_1.png");
    }

    // caso o jogador morra
    if(GameData::hp_atual <=0 ){

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

        GameData::checkPointX = 0;
        GameData::checkPointY = 0;

    }

    //refaz essas variaveis para o calculo de impacto com o solo
    caindo = true;
    agarrado = false;
    pulando = false;
    parado = false;

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
// variavel ultimo contato adicionada para o jogador ao cair voltar ao ultimo lugar que pisou
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
            ultimoContatoX = associated.box.x;

            if(ultimoContatoX < chao->getX()){
                ultimoContatoX = chao->getX();
            }                    
            else if(ultimoContatoX > chao->getX() + chao->getLength() - largura){
                ultimoContatoX = chao->getX() + chao->getLength() - largura;
            }
            if(posy_anterior < associated.box.y){
                caiu = true;
                sons->Stop();
                sons->setSound("./assets/audio/queda.wav");
                sons->Play();                       
            }
            ultimoContatoY = associated.box.y;
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
                    ultimoContatoX = associated.box.x;

                    if(ultimoContatoX < chao->getX()){
                        ultimoContatoX = chao->getX();
                    }                    
                    else if(ultimoContatoX > chao->getX() + chao->getLength() - largura){
                        ultimoContatoX = chao->getX() + chao->getLength() - largura;
                    }
                    if(posy_anterior < associated.box.y){
                        caiu = true;
                        sons->Stop();
                        sons->setSound("./assets/audio/queda.wav");
                        sons->Play();                       
                    }
                    ultimoContatoY = associated.box.y;
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

                    ultimoContatoX = associated.box.x;
                    if(ultimoContatoX < chao->getX()){
                        ultimoContatoX = chao->getX();
                    }
                    else if(ultimoContatoX > chao->getX() + chao->getLength() - largura){
                        ultimoContatoX = chao->getX() + chao->getLength() - largura;
                    }
                    if(posy_anterior < associated.box.y){
                        caiu = true;
                        sons->Stop();
                        sons->setSound("./assets/audio/queda.wav");
                        sons->Play();                       
                    }                    
                    ultimoContatoY = associated.box.y;
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
    // e volta ao ultimo lugar que ele pisou, reseta a stamina
    if(chao->getTipo() == "lava"){

        GameData::hp_atual = GameData::hp_atual - 1;
        associated.box.x = GameData::checkPointX;
        associated.box.y = GameData::checkPointY;
        speed.x = 0;
        speed.y = 0;
        GameData::stamina_atual = GameData::stamina_total;
        sons->Stop();
        sons->setSound("./assets/audio/dano.wav");
        sons->Play();
        damaged = true;

    }
    // caso seja de um tipo checkpoint e o jogador apertar x
    // o checkpoint do jogador eh atualizado para a posicao do bloco
      if(chao->getTipo() == "checkpoint"){

        if(InputManager :: GetInstance().KeyPress(SDLK_x)){
            GameData::checkPointX = chao->getX();
            GameData::checkPointY = chao->getY();
        }

    }  
}