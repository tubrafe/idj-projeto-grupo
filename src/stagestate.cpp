#include "../include/stagestate.h"
#include "../include/inputmanager.h"
#include "../include/camera.h"
#include "../include/camerafollower.h"
#include "../include/alien.h"
#include "../include/penguinbody.h"
#include "../include/collider.h"
#include "../include/endstate.h"
#include "../include/gamedata.h"
#include "../include/game.h"
#include "../include/bloco.h"
#include "../include/jogador.h"
#include <cmath>




StageState :: StageState () {

	backgroundMusic = nullptr;
	tileSet = nullptr;

	started = false;
    quitRequested = false;

	GameData::playerVictory = false;
    

}

StageState :: ~StageState(){

    objectArray.clear();
	

}


void StageState :: LoadAssets() {

	GameObject *objeto = new GameObject();


	Sprite* bg = new Sprite(*objeto,"./assets/img/forest.jpg");
	objeto->box.x = 0;
	objeto->box.y = 0;
	
	CameraFollower* seguidor = new CameraFollower(*objeto);

	objeto->AddComponent(bg);
	objeto->AddComponent(seguidor);
	objectArray.emplace_back(objeto);



/*	GameObject *outro = new GameObject();

	TileSet *tile = new TileSet(64,64,"./assets/img/tileset.png");
	TileMap *mapa = new TileMap(*outro,"./assets/map/tileMap.txt",tile);


	outro->AddComponent(mapa);
	objectArray.emplace_back(outro);
*/
	GameObject* chao = new GameObject();

	Bloco* plataforma = new Bloco(*chao,"./assets/img/bloco.png",750,750);

	chao->AddComponent(plataforma);
	objectArray.emplace_back(chao);


	GameObject* chao2 = new GameObject();

	Bloco* plataforma2 = new Bloco(*chao2,"./assets/img/bloco.png",2300,750);

	chao2->AddComponent(plataforma2);
	objectArray.emplace_back(chao2);





	GameObject* player = new GameObject();

	player->box.x = 750;
	player->box.y = 690;

	Jogador* jogador = new Jogador(*player);

    Sprite* personagem = new Sprite(*player,"./assets/img/sonic.png" );

    Collider* colisor = new Collider(*player);

    player->AddComponent(personagem);	
	player->AddComponent(jogador);
    player->AddComponent(colisor);
	
	Camera ::Follow(player);
	objectArray.emplace_back(player);





/*
	int i;

	for(i=0;i<4;i++){

		GameObject *inimigo = new GameObject();




		int x = 750,y =750;
		
		while((x <= 1050) and (x>=550)){

			x = rand()%2000;

		}
		while((y <= 1050) and (y>=550)){

			y = rand()%2000;

		}


		inimigo->box.x = x;
		inimigo->box.y = y;

		Alien* alienigena = new Alien(*inimigo, rand()%(5-3+1)+3, rand()%5+1);

		inimigo->AddComponent(alienigena);
		objectArray.emplace_back(inimigo);
	}

*/
    backgroundMusic = new Music("./assets/audio/sonicphase.mp3");

}



void StageState :: Update (float dt) {
    int valor = objectArray.size();


    if(Jogador::player == nullptr){
        GameData::playerVictory = false;
        popRequested = true;
		EndState* fim = new EndState();
        Game::GetInstance().Push(fim);

    }


	else{
		if((InputManager :: GetInstance().KeyPress(SDLK_ESCAPE) == true) or (InputManager :: GetInstance().QuitRequested() == true)){

			popRequested = true;
			backgroundMusic->Stop();
			Camera::Unfollow();
			Camera::pos = Vec2(0,0);

		};
		Camera :: Update(dt);
		int i, j;
		for (i=0;i<valor;i++){
			
			objectArray[i]->Update(dt);


		};


		for (i=0;i<valor;i++){
			Collider *colisor = (Collider *)objectArray[i]->GetComponent("collider");

				
			if(colisor != nullptr){
				
				for(j=i+1;j<valor;j++){
					Collider *colidente = (Collider *)objectArray[j]->GetComponent("collider");

					if(colidente != nullptr){

						if(colisor->IsColliding(*colidente) == true){
							
							objectArray[i]->NotifyCollision(*objectArray[j]);
							objectArray[j]->NotifyCollision(*objectArray[i]);

						}


					}

				}

			}


		}






		for (i=0,j=objectArray.size();i<j;i++){

			if (objectArray[i]->IsDead() == true){
				
				objectArray.erase(objectArray.begin() + i);
				i--;
				j--;
			};


		};

	}


}


void StageState :: Render(){
    int valor = objectArray.size();
	
    int i;
    for (i=0;i<valor;i++){
		if(objectArray[i]->GetComponent("Jogador")){
			printf("camera : %f %f\n", objectArray[i]->box.x, objectArray[i]->box.y);

		}


		objectArray[i]->Render();			


    };

}







void StageState :: Start(){

    LoadAssets();
    backgroundMusic->Play();
	
	int valor = objectArray.size();
    for (int i=0;i<valor;i++){


        objectArray[i]->Start();


    };

	started = true;

}



void StageState :: Pause(){}



void StageState :: Resume(){}