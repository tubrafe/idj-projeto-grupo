#include "../include/sprite.h"
#include "../include/game.h"
#include "../include/resources.h"
#include "../include/camera.h"
#include <string>





Sprite :: Sprite(GameObject& associated) : Component(associated){

    texture = nullptr;
    scale.x = 1;
    scale.y = 1;

}



Sprite :: Sprite(GameObject& associated, std :: string file, int frameCount, float frameTime, float secondsToSelfDestruct) : Component(associated){
    texture = nullptr;
    temporario = nullptr;
    scale.x = 1;
    scale.y = 1;
    Open(file);
    SetFrameCount(frameCount);
    SetFrameTime(frameTime);
    this->secondsToSelfDestruct = secondsToSelfDestruct;

    selfDestructCount = new Timer();
    piscar = 0;


}





Sprite :: ~Sprite(){


    // Resources :: ClearImage();


}


void Sprite :: Open (std :: string file){


    const char * c = file.c_str();
    texture = Resources :: GetImage(file).get();
    temporario = Resources :: GetImage(file).get();


    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0,0,width,height);
    associated.box.h = height;
    associated.box.w = width;

}

void Sprite :: SetClip (int x, int y, int w, int h) {

    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;

}


void Sprite :: Render (){

    Render(associated.box.x- Camera :: pos.x, associated.box.y - Camera :: pos.y);

}


void Sprite :: Render (int x, int y){

    SDL_Rect temp;
    temp.x = x + (clipRect.w/2 - (clipRect.w/2*scale.x));
    temp.y = y + (clipRect.h/2 - (clipRect.h/2*scale.y));
    temp.h = clipRect.h * scale.y;
    temp.w = clipRect.w * scale.x;


    SDL_RenderCopyEx(Game :: GetInstance ().GetRenderer(), texture, &clipRect, &temp, associated.angleDeg ,nullptr,SDL_FLIP_NONE);


}


int Sprite :: GetWidth(){

    return (width/frameCount) * scale.x;

}

int Sprite :: GetHeight(){

    return height * scale.y;

}



bool Sprite :: IsOpen(){

    if (texture != NULL) {
        return true;

    };

    return false;
}




bool Sprite :: Is(std :: string type){

    if(type == "sprite"){
        return true;
    };
    return false;


}



void Sprite :: Update(float dt){
    if(secondsToSelfDestruct > 0){
        selfDestructCount->Update(dt);
           
        if(selfDestructCount->Get() > secondsToSelfDestruct){
 
            associated.RequestDelete();
        }
    }


    timeElapsed = timeElapsed + dt;



    if(timeElapsed >= frameTime){
        if(currentFrame+1 == frameCount){
            SetFrame(0);
        }
        else{
            SetFrame(currentFrame+1);
        }
    }

    if(piscar != 0){
        if(texture == nullptr){
            texture = temporario;
        }
        else{
            texture = nullptr;
        }
        piscar = 0;
    }

}


void Sprite :: SetScaleX(float scaleX, float scaleY){
    


    
    if(scaleX != 0){
        scale.x = scaleX;
    }
    
    if(scaleY != 0){
        scale.y = scaleY;
    }



}



Vec2 Sprite ::  GetScale(){

    return scale;


}

void Sprite :: SetFrame (int frame){


    this->currentFrame = frame;

    timeElapsed = 0;

    SetClip(GetWidth()*currentFrame/scale.x,0,width/frameCount,height);

}



void Sprite :: SetFrameCount (int frameCount){


    this->frameCount = frameCount;
    SetFrame(0);
    associated.box.w = GetWidth();


}
        
        
        
void Sprite :: SetFrameTime (float frameTime){


    this->frameTime = frameTime;
    timeElapsed = 0;


}


void Sprite :: setPiscar(){

    piscar = 1;

}

void Sprite :: setOriginal(){

    texture = temporario;

}


void Sprite :: setTexture(std::string textura){

    this->Open(textura);


}

