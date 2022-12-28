#include <iostream>
#include "../include/game.h"

// roda o jogo
int main  (int   argc   , char**   arg){


    TitleState* titulo = new TitleState();
    Game :: GetInstance ().Push(titulo);
    Game::GetInstance().Run();


}