#include "../include/sound.h"
#include "../include/resources.h"




// controla as funcoes referentes aos sons do jogo



Sound :: Sound(GameObject& associated): Component(associated){


    chunk = nullptr;

}



Sound :: Sound(GameObject& associated, std::string file): Component(associated){

    Open(file);


}



void Sound :: Play(int times){


    channel = Mix_PlayChannel(-1, chunk, times-1);

}


void Sound :: Stop() {


    if (chunk != nullptr){
        Mix_HaltChannel(channel);
    };


}


void Sound :: Open(std::string file){

    chunk = Resources :: GetSound(file).get();

}


Sound :: ~Sound(){

}



bool Sound :: IsOpen(){

    if (chunk == nullptr){
        return false;
    };

    return true;



}



void Sound :: Update(float dt){}



void Sound :: Render(){}



bool Sound :: Is(std::string type){

    if(type == "sound"){
        return true;
    };
    return false;

}
