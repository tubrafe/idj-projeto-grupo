#include "../include/camerafollower.h"
#include "../include/camera.h"



CameraFollower :: CameraFollower(GameObject& associated) : Component(associated){}



void CameraFollower :: Update(float dt){

    associated.box.x = Camera :: pos.x;
    associated.box.y = Camera :: pos.y; 


}


void CameraFollower :: Render(){}


bool CameraFollower :: Is(std :: string type){

    if (type == "camerafollower"){
        return true;
    };
    return false;

}