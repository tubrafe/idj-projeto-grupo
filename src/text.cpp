#include "../include/text.h"
#include "../include/game.h"

// controla textos criados no jogo (no momento apenas usado na tella inicial e final)

Text :: Text (GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, float tempo) : Component(associated){


    this->fontFile = fontFile;

    this->fontSize = fontSize;

    this->text = text;

    this->color = color;
    auxiliar = color;

    texture = nullptr;

    font = Resources::GetFont(fontFile, fontSize);


    timer = new Timer();
    cooldown = tempo;

    this->style = style;

    RemakeTexture();




}



Text :: ~Text (){

    if(texture != nullptr){
        SDL_DestroyTexture(texture);
    }
    texture = nullptr;

}



void Text :: Update (float dt){

    if(cooldown > 0){

        timer->Update(dt);

        if(timer->Get() > cooldown){


            if(color.a != 0){
                color = SDL_Color{0,0,0,0};
            }
            else{
                color = auxiliar;
            }

            SetColor(color);
            timer->Restart();
        }
    }





}



void Text :: Render (){

    if(texture != nullptr){

        SDL_Rect clipRect;
        SDL_Rect destRect;

        
        clipRect.x = 0;
        clipRect.y = 0;
        clipRect.h = associated.box.h;
        clipRect.w = associated.box.w;


        destRect.x = associated.box.x-Camera::pos.x;
        destRect.y = associated.box.y-Camera::pos.y;
        destRect.h = clipRect.h;
        destRect.w = clipRect.w;

        SDL_RenderCopy(Game::GetInstance().GetRenderer(),texture,&clipRect,&destRect);


    }

    
}



bool Text :: Is (std::string type){

    if(type == "text"){
        return true;
    };
    return false;



}



void Text :: SetText (std::string text){

    this->text = text;

    RemakeTexture();


}


void Text :: SetColor (SDL_Color color){

    this->color = color;

    RemakeTexture();


}    
        
        
void Text :: SetStyle (TextStyle style){

    this->style = style;

    RemakeTexture();


}


void Text :: SetFontFile (std::string fontFile){

    this->fontFile = fontFile;

    RemakeTexture();

}




void Text :: SetFontSize (int fontSize){

    this->fontSize = fontSize;


    RemakeTexture();

}




void Text :: RemakeTexture (){

    SDL_Surface* temp = nullptr; 

    if(texture != nullptr){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }

    if(style == SOLID){
        const char * c = text.c_str();
        temp = TTF_RenderText_Solid(font.get(), c, color);
    }
    else if(style == SHADED){
        const char * c = text.c_str();
        temp = TTF_RenderText_Shaded(font.get(), c, color,SDL_Color{0,0,0,0});

    }
    else{
        const char * c = text.c_str();
        temp = TTF_RenderText_Blended(font.get(), c, color);


    }

    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), temp);


    SDL_FreeSurface(temp);

    int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	associated.box.w = w;
	associated.box.h = h;
} 


// atualiza a posicao do texto
void Text :: SetPos (Vec2 pos){

    associated.box.x = pos.x;
    associated.box.y = pos.y;
}
