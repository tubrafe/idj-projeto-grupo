#ifndef MUSIC_H
#define MUSIC_H

#define INCLUDE_SDL_MIXER
#include <iostream>
#define INCLUDE_SDL
#include "SDL_include.h"
#include <string>




class Music {

    public:
        Music();
        Music(std :: string file);
        ~Music();
        void Play(int times = -1);
        void Stop (int msToStop = 1500);
        void Open (std :: string file);
        bool IsOpen();

    private:
        Mix_Music* music;


};

#endif