#include "../include/timer.h"




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