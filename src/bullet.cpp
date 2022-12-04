#include "../include/bullet.h"
#include "../include/sprite.h"
#include "../include/gameobject.h"
#include "../include/collider.h"



Bullet :: Bullet(GameObject& associated , float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetsPlayer) : Component(associated){


    Sprite* bala = new Sprite(associated,sprite, frameCount, frameTime);


    this->targetsPlayer = targetsPlayer;
    this->associated.AddComponent(bala);

    this->damage = damage;

    distanceLeft = maxDistance;

    this->speed = Vec2(1,0).GetRotated(angle);
    associated.angleDeg = angle*180/M_PI;

    this->speed.x = this->speed.x*speed;
    this->speed.y = this->speed.y*speed;

    Collider* colisor = new Collider(associated);
    this->associated.AddComponent(colisor);



}



void Bullet :: Update (float dt){
    

    Vec2 posic_atual = Vec2(associated.box.x, associated.box.y);

    Vec2 destino;

    destino.x = associated.box.x - (associated.box.w/2);
    destino.y = associated.box.y - (associated.box.h/2);


    //speed.x = speed.x + (destino.x - posic_atual.x);
    //speed.y = speed.y + (destino.y - posic_atual.y);

     posic_atual.x = posic_atual.x + (speed.x*dt);
     posic_atual.y = posic_atual.y + (speed.y*dt);

    associated.box.x = posic_atual.x;
    associated.box.y = posic_atual.y;

    distanceLeft = distanceLeft - Vec2(speed.x*dt,speed.y*dt).magnitude();


    if(distanceLeft <= 0){
        

        associated.RequestDelete();
    }

    




}


void Bullet :: Render (){}


bool Bullet ::  Is(std::string type){

    if (type == "Bullet"){
        return true;
    };
    return false;

}




int Bullet :: GetDamage (){

    return damage;


}