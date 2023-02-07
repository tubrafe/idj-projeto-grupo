#ifndef SOUND_H
#define SOUND_H


#include <iostream>
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "component.h"


class Sound : public Component {

    public:
        Sound(GameObject& associated);
        Sound(GameObject& associated, std::string file);
        ~Sound();
        void Play(int times = 1);
        void Stop();
        void Open(std::string file);
        bool IsOpen();
        
        void Update(float dt);
        void Render();
        bool Is(std::string type);

        void setSound(std::string file);




    private:
        Mix_Chunk* chunk;
        int channel;


};


#endif