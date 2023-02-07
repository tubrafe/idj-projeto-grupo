#include "../include/titlestate.h"
#include "../include/inputmanager.h"
#include "../include/game.h"
#include "../include/stagestate.h"
#include "../include/camera.h"
#include "../include/text.h"

// tela incial do jogo

TitleState :: TitleState(){

    GameObject* objeto = new GameObject();
    objeto->box.x = 0;
    objeto->box.y = 0;

    Sprite* tela = new Sprite(*objeto,"./assets/img/title.jpg");

    objeto->AddComponent(tela);

    objectArray.emplace_back(objeto);


    GameObject* texto = new GameObject();

    Text* titulo = new Text (*texto, "./assets/font/Call me maybe.ttf", 50, Text::BLENDED, "Aperte espaco para comecar!", SDL_Color{255, 0, 0, 255}, 0.5);

    texto-> box.x = 200;
    texto-> box.y = 500;

    texto->AddComponent(titulo);
    objectArray.emplace_back(texto);

    timer = new Timer();
    cooldown = 0.2;

    backgroundMusic = new Music("./assets/audio/titulo.mp3");

}



void TitleState::Update(float dt){

    if((InputManager :: GetInstance().KeyPress(SDLK_ESCAPE)) or (InputManager :: GetInstance().QuitRequested() == true)){
        quitRequested = true;
    }
    if(InputManager :: GetInstance().KeyPress(SDLK_SPACE)){
        State* estado = new StageState();
        Game::GetInstance().Push(estado);
    }
    UpdateArray(dt);

}



TitleState :: ~TitleState(){
    objectArray.clear();
}

void TitleState::Start(){
    backgroundMusic->Play();
}

void TitleState::LoadAssets(){}

void TitleState::Render(){

    Camera::pos = Vec2(0,0);

    RenderArray();

}

void TitleState::Resume() {}

void TitleState::Pause() {}