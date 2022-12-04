#include "../include/state.h"



State :: State(){

    quitRequested = false;
    popRequested = false;
    started = false;



}


State :: ~State(){

    objectArray.clear();

}



std::weak_ptr< GameObject > State :: AddObject(GameObject* go){


	std::shared_ptr< GameObject > novo(go);


	objectArray.push_back(novo);

	if(started){

		
		go->Start();

	};

	std::weak_ptr<GameObject> retorno(novo);

	return retorno;


}








std::weak_ptr< GameObject > State :: GetObjectPtr(GameObject* go){


	int valor = objectArray.size();

	int i;
    for (i=0;i<valor;i++){
		
        if(objectArray[i].get() == go){

			std::weak_ptr<GameObject> retorno(objectArray[i]);
			return retorno;

		};


    };

	std::weak_ptr<GameObject> retorno;

	return retorno;


}



bool State :: QuitRequested(){

    return quitRequested;

}



bool State :: PopRequested(){

    return popRequested;

}


void State :: StartArray(){

    int valor = objectArray.size();
	
    int i;
    for (i=0;i<valor;i++){

		objectArray[i]->Start();			

    };

}
        
        
void State :: UpdateArray(float dt){

    int valor = objectArray.size();
	
    int i;
    for (i=0;i<valor;i++){

		objectArray[i]->Update(dt);			

    };



}  



void State :: RenderArray(){

    int valor = objectArray.size();
	
    int i;
    for (i=0;i<valor;i++){

		objectArray[i]->Render();			

    };


}