#include <iostream>
#include "../include/game.h"

int main  (int   argc   , char**   arg){


    TitleState* titulo = new TitleState();
    Game :: GetInstance ().Push(titulo);
    Game::GetInstance().Run();


}