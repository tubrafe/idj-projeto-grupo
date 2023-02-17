#include "../include/endstate.h"
#include "../include/gamedata.h"
#include "../include/camera.h"
#include "../include/text.h"
#include "../include/inputmanager.h"
#include "../include/titlestate.h"
#include "../include/game.h"

EndState :: EndState(){

    Camera::pos = Vec2(0,0);
    bool temp = GameData::playerVictory;

    //caso o jogador venca
    if(temp == true){

        GameObject* bg = new GameObject();
        bg->box.x = 0;
        bg->box.y = 0;

        Sprite* tela = new Sprite(*bg,"./assets/img/win.jpg");
        bg->AddComponent(tela);
        objectArray.emplace_back(bg);

        GameObject* texto = new GameObject();
        texto-> box.x = 150;
        texto-> box.y = 550;

        Text* titulo = new Text (*texto, "./assets/font/Abel-Regular.ttf", 30, Text::BLENDED, "Aperte Esc para sair ou espaco para tentar novamente!", SDL_Color{255, 0, 0, 255}, 0.5); 
        texto->AddComponent(titulo);
        objectArray.emplace_back(texto);

        backgroundMusic = new Music("./assets/audio/Tema_Final.wav");

    }
    //caso o jogador perca
    else{

        GameObject* bg = new GameObject();
        bg->box.x = 0;
        bg->box.y = 0;

        Sprite* tela = new Sprite(*bg,"./assets/img/lose.png");
        bg->AddComponent(tela);
        objectArray.emplace_back(bg);

        GameObject* texto = new GameObject();
        texto-> box.x = 150;
        texto-> box.y = 550;

        Text* titulo = new Text (*texto, "./assets/font/Abel-Regular.ttf", 30, Text::BLENDED, "Aperte Esc para sair ou espaco para tentar novamente!", SDL_Color{255, 0, 0, 255}, 0.5); 
        texto->AddComponent(titulo);
        objectArray.emplace_back(texto);

        backgroundMusic = new Music("./assets/audio/Tema_Derrota.wav");



    }





}


EndState::~EndState(){

    objectArray.clear();
    backgroundMusic->Stop();

}


void EndState::Render(){

    Camera::pos = Vec2(0,0);

    RenderArray();

}


void EndState :: Update(float dt){


    // espera resposta do jogador
	
	if((InputManager::GetInstance().KeyPress(SDLK_ESCAPE)) or (InputManager::GetInstance().QuitRequested())){
		quitRequested = true;
    }
    if(InputManager::GetInstance().KeyPress(SDLK_SPACE)){
        popRequested = true;
        TitleState* novo = new TitleState();
        Game::GetInstance().Push(novo);
    }
    UpdateArray(dt);



}



void EndState :: LoadAssets(){}

void EndState :: Start(){

    backgroundMusic->Play();
}

void EndState :: Pause(){}

void EndState :: Resume(){}
