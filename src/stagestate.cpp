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
#include <sstream>
#include <iomanip>

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

	std::getline(save, linha);
	GameData::hp_atual = std::stoi(linha);

	GameData::hp_total = 5;
	GameData::stamina_total = 5;
	GameData::stamina_atual = 5;
	
	std::getline(save, linha);
	GameData::item = std::stoi(linha);


}

StageState :: ~StageState(){

    objectArray.clear();
	

}


void StageState :: LoadAssets() {

	GameObject *objeto = new GameObject();


	Sprite* bg = new Sprite(*objeto,"./assets/img/montanhas.png");
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

	Bloco* plataforma = new Bloco(*chao,"./assets/img/plataforma_1.png",750,800, "terra", Vec2(1,1));

	chao->AddComponent(plataforma);
	objectArray.emplace_back(chao);


	GameObject* chao2 = new GameObject();

	Bloco* plataforma2 = new Bloco(*chao2,"./assets/img/plataforma_1.png",1600,800, "terra", Vec2(1,1));

	chao2->AddComponent(plataforma2);
	objectArray.emplace_back(chao2);


	GameObject* lava = new GameObject();

	Bloco* perigo = new Bloco(*lava,"./assets/img/lava.png",700,1200, "lava", Vec2(4,1.2));

	lava->AddComponent(perigo);
	objectArray.emplace_back(lava);

	if(GameData::item == 0){
			GameObject* mascara = new GameObject();

			Bloco* gas_mask = new Bloco(*mascara,"./assets/img/gas_mask_2.png",1000,640, "mascara", Vec2(1,1));

			mascara->AddComponent(gas_mask);
			objectArray.emplace_back(mascara);

	}


	GameObject* checkpoint = new GameObject();

	Bloco* fogueira = new Bloco(*checkpoint,"./assets/img/camp_aceso.png",900,640, "checkpoint", Vec2(1,1));

	checkpoint->AddComponent(fogueira);
	objectArray.emplace_back(checkpoint);


	GameObject* checkpoint2 = new GameObject();

	Bloco* fogueira2 = new Bloco(*checkpoint2,"./assets/img/camp_aceso.png",1500,640, "checkpoint", Vec2(1,1));

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



	GameObject* vida = new GameObject();

	std::string hud = std::to_string(GameData::hp_atual) + "I" + std::to_string(GameData::hp_total) + "\n" + std::to_string(GameData::stamina_atual) + "." + std::to_string(GameData::stamina_total) + + "\n" + std::to_string(GameData::item) ;

	vida->box.x = Camera::GetPos().x; 
	vida->box.y = Camera::GetPos().y - 25; 

	Text* info = new Text(*vida, "./assets/font/Call me maybe.ttf", 50, Text::BLENDED, hud, SDL_Color{255, 0, 0, 255});

	hp = info;

	vida->AddComponent(info);
	objectArray.emplace_back(vida);



	GameObject* estamina = new GameObject();



	std::stringstream sta_atual;
	sta_atual << std::fixed << std::setprecision(1) << GameData::stamina_atual;
	std::string atual = sta_atual.str();

	std::stringstream sta_total;
	sta_total << std::fixed << std::setprecision(1) << GameData::stamina_total;
	std::string total = sta_total.str();

	std::string hud2 = atual + " " + total;

	estamina->box.x = Camera::GetPos().x; 
	estamina->box.y = Camera::GetPos().y + 25; 

	Text* info2 = new Text(*estamina, "./assets/font/Call me maybe.ttf", 50, Text::BLENDED, hud2, SDL_Color{255, 0, 0, 255});

	stamina = info2;

	estamina->AddComponent(info2);
	objectArray.emplace_back(estamina);


	GameObject* n_item = new GameObject();

	std::stringstream item;
	item << std::fixed << std::setprecision(1) << GameData::item;
	std::string itemizacao = item.str();

	std::string hud3 = itemizacao;

	n_item->box.x = Camera::GetPos().x; 
	n_item->box.y = Camera::GetPos().y + 75; 

	Text* info3 = new Text(*n_item, "./assets/font/Call me maybe.ttf", 50, Text::BLENDED, hud3, SDL_Color{255, 0, 0, 255});

	mascara = info3;

	n_item->AddComponent(info3);
	objectArray.emplace_back(n_item);

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
    backgroundMusic = new Music("./assets/audio/fase.mp3");

}



void StageState :: Update (float dt) {
    int valor = objectArray.size();


    if(Jogador::player == nullptr){
		//salva no arquivo as variaveis caso o jogador morra
			std::ofstream save ("./assets/save/save.txt"); 
			std::string salvar = std::to_string(GameData::checkPointX);
			salvar.append("\n");
			salvar.append(std::to_string(GameData::checkPointY));
			salvar.append("\n");
			salvar.append(std::to_string(GameData::hp_atual));
			salvar.append("\n");
			salvar.append(std::to_string(GameData::item));


			save << salvar << endl;
			save.close();

        GameData::playerVictory = false;
        popRequested = true;
		EndState* fim = new EndState();
        Game::GetInstance().Push(fim);

    }


	else{
		if((InputManager :: GetInstance().KeyPress(SDLK_ESCAPE) == true) or (InputManager :: GetInstance().QuitRequested() == true)){

			//salva no arquivo as variaveis caso o jogador feche o jogo
			std::ofstream save ("./assets/save/save.txt"); 
			std::string salvar = std::to_string(GameData::checkPointX);
			salvar.append("\n");
			salvar.append(std::to_string(GameData::checkPointY));
			salvar.append("\n");
			salvar.append(std::to_string(GameData::hp_atual));
			salvar.append("\n");
			salvar.append(std::to_string(GameData::item));
			

			save << salvar << endl;
			save.close();
			popRequested = true;
			backgroundMusic->Stop();
			Camera::Unfollow();
			Camera::pos = Vec2(0,0);

		};
		Camera :: Update(dt);
		int i, j;

		//atualiza a posicao da hud(vida e stamina na tela) para acompanhar a camera
		for (i=0;i<valor;i++){
			Jogador* player = (Jogador*)objectArray[i]->GetComponent("Jogador");

			if(player != nullptr){
				hp->SetPos(Vec2(Camera::GetPos().x, Camera::GetPos().y - 25));
				std::string hud = std::to_string(GameData::hp_atual) + " I " + std::to_string(GameData::hp_total);
				hp->SetText(hud);

				stamina->SetPos(Vec2(Camera::GetPos().x, Camera::GetPos().y + 25));
				std::stringstream sta_atual;
				sta_atual << std::fixed << std::setprecision(1) << GameData::stamina_atual;
				std::string atual = sta_atual.str();

				std::stringstream sta_total;
				sta_total << std::fixed << std::setprecision(1) << GameData::stamina_total;
				std::string total = sta_total.str();

				std::string hud2 = atual + " " + total;


				stamina->SetText(hud2);

				mascara->SetPos(Vec2(Camera::GetPos().x, Camera::GetPos().y + 75));
				std::string hud3 = std::to_string(GameData::item) ;
				
				mascara->SetText(hud3);
			}
		}
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