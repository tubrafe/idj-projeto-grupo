#include "../include/music.h"
#include "../include/resources.h"
#include <string>





Music :: Music(){

    music = nullptr;

}


Music :: Music(std :: string file){

    music = nullptr;

    Open(file);

}

void Music :: Play(int times) {


    Mix_PlayMusic(music, times);


}




void Music :: Stop (int msToStop) {


    Mix_FadeOutMusic(msToStop);


}


void Music :: Open (std :: string file){

    music = Resources :: GetMusic(file).get();



}


bool Music :: IsOpen(){

    if (music != NULL) {
        return true;

    };

    return false;



}

Music :: ~Music (){


    Stop();
    Mix_FreeMusic(music);


    
}