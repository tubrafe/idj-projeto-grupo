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

        Text* titulo = new Text (*texto, "./assets/font/Call me maybe.ttf", 30, Text::BLENDED, "Aperte Esc para sair ou espaco para tentar novamente!", SDL_Color{255, 0, 0, 255}, 0.5); 
        texto->AddComponent(titulo);
        objectArray.emplace_back(texto);

        backgroundMusic = new Music("./assets/audio/endStateWin.ogg");

    }
    else{

        GameObject* bg = new GameObject();
        bg->box.x = 0;
        bg->box.y = 0;

        Sprite* tela = new Sprite(*bg,"./assets/img/lose.jpg");
        bg->AddComponent(tela);
        objectArray.emplace_back(bg);

        GameObject* texto = new GameObject();
        texto-> box.x = 150;
        texto-> box.y = 550;

        Text* titulo = new Text (*texto, "./assets/font/Call me maybe.ttf", 30, Text::BLENDED, "Aperte Esc para sair ou espaco para tentar novamente!", SDL_Color{255, 0, 0, 255}, 0.5); 
        texto->AddComponent(titulo);
        objectArray.emplace_back(texto);

        backgroundMusic = new Music("./assets/audio/endStateLose.ogg");



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
