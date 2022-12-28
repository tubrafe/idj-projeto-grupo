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
#include <fstream>

using namespace std;

// loop do jogo principal

StageState :: StageState () {

	backgroundMusic = nullptr;
	tileSet = nullptr;

	started = false;
    quitRequested = false;

	GameData::playerVictory = false;

	std::ifstream save ("./assets/save/save.txt"); 
	std::string linha;

	std::getline(save, linha);
	GameData::checkPointX = std::stof(linha);
    
	std::getline(save, linha);
	GameData::checkPointY = std::stof(linha);

	printf("%f %f\n", GameData::checkPointX, GameData::checkPointY);
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


// n esta sendo usado tilemap no momento
/*	GameObject *outro = new GameObject();

	TileSet *tile = new TileSet(64,64,"./assets/img/tileset.png");
	TileMap *mapa = new TileMap(*outro,"./assets/map/tileMap.txt",tile);


	outro->AddComponent(mapa);
	objectArray.emplace_back(outro);
*/
	GameObject* chao = new GameObject();

	Bloco* plataforma = new Bloco(*chao,"./assets/img/bloco.png",750,750, "terra", Vec2(1,1.5));

	chao->AddComponent(plataforma);
	objectArray.emplace_back(chao);


	GameObject* chao2 = new GameObject();

	Bloco* plataforma2 = new Bloco(*chao2,"./assets/img/bloco.png",2200,750, "terra", Vec2(1,1.5));

	chao2->AddComponent(plataforma2);
	objectArray.emplace_back(chao2);


	GameObject* lava = new GameObject();

	Bloco* perigo = new Bloco(*lava,"./assets/img/lava.png",700,1200, "lava", Vec2(4,1.2));

	lava->AddComponent(perigo);
	objectArray.emplace_back(lava);



	GameObject* checkpoint = new GameObject();

	Bloco* fogueira = new Bloco(*checkpoint,"./assets/img/camp_aceso.png",900,640, "checkpoint", Vec2(1,1));

	checkpoint->AddComponent(fogueira);
	objectArray.emplace_back(checkpoint);


	GameObject* checkpoint2 = new GameObject();

	Bloco* fogueira2 = new Bloco(*checkpoint2,"./assets/img/camp_aceso.png",2500,640, "checkpoint", Vec2(1,1));

	checkpoint2->AddComponent(fogueira2);
	objectArray.emplace_back(checkpoint2);



	GameObject* player = new GameObject();

	player->box.x = GameData::checkPointX;
	player->box.y = GameData::checkPointY;

	Jogador* jogador = new Jogador(*player);



    Collider* colisor = new Collider(*player);

	
	player->AddComponent(jogador);
    player->AddComponent(colisor);
	
	Camera ::Follow(player);
	objectArray.emplace_back(player);




// n usado pq n ha aliens atualmente
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
    backgroundMusic = new Music("./assets/audio/TRY.mp3");

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


			std::ofstream save ("./assets/save/save.txt"); 
			std::string salvar = std::to_string(GameData::checkPointX);
			salvar.append("\n");
			salvar.append(std::to_string(GameData::checkPointY));


			save << salvar << endl;
			save.close();
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