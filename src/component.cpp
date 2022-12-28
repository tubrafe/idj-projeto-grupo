/*base para todo game object*/

#include "../include/component.h"
#include "../include/gameobject.h"




Component ::  Component(GameObject& associated) :associated(associated){} ;
Component :: ~Component(){};
void Component :: Update(float dt){};
void Component :: Render() {};
bool Component :: Is(std :: string type){};
void Component :: Start(){};
void Component :: NotifyCollision( GameObject& other){};
