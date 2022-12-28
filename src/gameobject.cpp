#include "../include/gameobject.h"
#include "../include/component.h"

//todas as funcoes referentes aos gameobjects

GameObject :: GameObject(){

    isDead = false;
    started = false;
    angleDeg = 0;


}



GameObject :: ~GameObject(){

    int valor = components.size()-1;

    int i;
    for (i=valor;i>=0;i--){

        components.erase(components.begin() + i);


    };
    components.clear();

}




void GameObject :: Update(float dt){

    int valor = components.size();
    int i;
    for (i=0;i<valor;i++){
        
        components[i]->Update(dt);


    };


}



void GameObject :: Render(){

    int valor = components.size();

    int i;
    for (i=0;i<valor;i++){
        components[i]->Render();
    };


}

bool GameObject :: IsDead(){

    return isDead;


}



void GameObject :: RequestDelete(){


    isDead = true;


}


void GameObject :: AddComponent(Component* cpt){


    components.emplace_back(cpt);



}


void GameObject ::  RemoveComponent(Component* cpt){


    int valor = components.size();

    int i;
    for (i=0;i<valor;i++){

        if (components[i].get() == cpt){
            components.erase(components.begin() + i);
            i--;
        };


    };



}


Component* GameObject :: GetComponent(std::string type){


    int valor = components.size();

    int i;
    for (i=0;i<valor;i++){

        if (components[i]->Is(type) == true){
            return  components[i].get();
        };


    };

    return nullptr;



}



void GameObject :: Start(){

    int valor = components.size();  

    int i;
    for (i=0;i<valor;i++){

        components[i]->Start();


    };
    started = true;



}



void GameObject :: NotifyCollision (GameObject& other){

    int i;
    int valor = components.size();

    for(i=0;i<valor;i++){

        components[i]->NotifyCollision(other);

    }


}