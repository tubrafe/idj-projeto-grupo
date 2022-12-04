#ifndef SPRITE_H
#define SPRITE_H


#include <iostream>
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include <string>
#include "component.h"
#include "vec2.h"
#include "timer.h"

class Sprite : public Component{

    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, std :: string file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct =  0);
        ~Sprite();
        void Open (std :: string file);
        void SetClip (int x, int y, int w, int h);
        void Render();
        void Render (int x, int y);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        
        void Update(float dt);
        bool Is(std::string type);

        void SetScaleX(float scaleX, float scaleY);
        Vec2 GetScale();

        void SetFrame (int frame);
        void SetFrameCount (int frameCount);
        void SetFrameTime (float frameTime);

        void setPiscar ();
        void setOriginal();

        void setTexture(std::string textura);


    private:
        SDL_Texture* texture;
        int width;
        int height;
        SDL_Rect clipRect;

        Vec2 scale;
    
        int frameCount;
        int currentFrame;
        float timeElapsed;
        float frameTime;
        int piscar;

        SDL_Texture* temporario; 

        Timer* selfDestructCount;
        float secondsToSelfDestruct;


};


#endif