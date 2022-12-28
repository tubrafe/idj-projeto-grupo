#include "../include/timer.h"


// funcoes para relogio

Timer :: Timer(){

    time = 0;


}



void Timer :: Update(float dt){

    time = time + dt;




}



void Timer :: Restart(){


    time = 0;


}



float Timer :: Get(){


    return time;


}