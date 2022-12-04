#include "../include/inputmanager.h"
#define INCLUDE_SDL
#include "../include/SDL_include.h"

#define LEFT_ARROW_KEY    SDLK_LEFT
#define RIGHT_ARROW_KEY   SDLK_RIGHT
#define UP_ARROW_KEY      SDLK_UP
#define DOWN_ARROW_KEY    SDLK_DOWN
#define ESCAPE_KEY        SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT



InputManager& InputManager :: GetInstance(){

    static InputManager retorno;

    return retorno;

}



InputManager :: InputManager(){

    int i;

    for(i=0;i<6;i++){

        mouseState[i] = false;

    };

    for(i=0;i<6;i++){

        mouseUpdate[i] = 0;

    };

    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    updateCounter = 0;


}



InputManager :: ~InputManager(){

    




}

void InputManager :: Update(){

    SDL_Event evento;

    SDL_GetMouseState(&mouseX, &mouseY);

    quitRequested = false;


                updateCounter = updateCounter + 1;
    while (SDL_PollEvent(&evento)) {

        if(evento.type == SDL_QUIT){
            quitRequested = true;

        };

        if(evento.type == SDL_MOUSEBUTTONDOWN){

            mouseState[evento.button.button] = true;

            mouseUpdate[evento.button.button] = updateCounter;


        };

        if(evento.type == SDL_MOUSEBUTTONUP){

            mouseState[evento.button.button] = false;

            mouseUpdate[evento.button.button] = updateCounter;


        };


        if(evento.type == SDL_KEYDOWN){
         
            if(evento.key.repeat != 1){

                keyState[evento.key.keysym.sym] = true;

                keyUpdate[evento.key.keysym.sym] = updateCounter;

            };
        };

        if(evento.type == SDL_KEYUP){
         
            if(evento.key.repeat != 1){

                keyState[evento.key.keysym.sym] = false;

                keyUpdate[evento.key.keysym.sym] = updateCounter;


            };


        };
    };
}


bool InputManager :: KeyPress(int key){

    if((keyUpdate[key]== updateCounter) and (keyState[key] == true)){
        return true;
    }

    return false;

}



bool InputManager :: KeyRelease(int key){

    if((keyUpdate[key]== updateCounter) and (keyState[key] == false)){

        return true;
    }

    return false;

}




bool InputManager :: IsKeyDown(int key){


    if(keyState[key] == true){
        return true;
    }

    return false;

} 






bool InputManager :: MousePress(int button){

    if((mouseUpdate[button]== updateCounter) and (mouseState[button] == true)){
        return true;
    }

    return false;



}



bool InputManager :: MouseRelease(int button){

    if((mouseUpdate[button]== updateCounter) and (mouseState[button] == false)){
        return true;
    }

    return false;



}



bool InputManager :: IsMouseDown(int button){

    if(mouseState[button] == true){
        return true;
    }

    return false;



}



bool InputManager :: QuitRequested(){

    return quitRequested;


}




int InputManager :: GetMouseX(){

    return mouseX;


}


int InputManager :: GetMouseY(){

    return mouseY;

}