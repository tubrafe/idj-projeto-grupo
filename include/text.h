#ifndef TEXT_H
#define TEXT_H


#include <iostream>
#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "component.h"
#include "vec2.h"
#include "rect.h"
#include "resources.h"
#include "camera.h"
#include "timer.h"

class GameObject;

class Text : public Component{

    public:
        enum TextStyle{SOLID, SHADED, BLENDED}; 

        Text (GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, float tempo = 0);
        ~Text ();

        void Update (float dt);
        void Render ();
        bool Is (std::string type);

        void SetText (std::string text);
        void SetColor (SDL_Color color);
        void SetStyle (TextStyle style);
        void SetFontFile (std::string fontFile);
        void SetFontSize (int fontSize);
        void SetPos(Vec2 pos);


    private:
        void RemakeTexture (); 

        std::shared_ptr<TTF_Font> font;
        SDL_Texture* texture;
        
        std::string  text;
        TextStyle style;
        std::string fontFile;
        int fontSize;
        SDL_Color color; 
        float cooldown;
        Timer* timer;
        SDL_Color auxiliar;


};


#endif