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
#include "../include/hud.h"
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

	construirMapa();


	GameObject* barra = new GameObject();
	Hud* barra_vida = new Hud(*barra,"../assets/img/vida_5.png");

	barra->AddComponent(barra_vida);
	objectArray.emplace_back(barra);


	GameObject* player = new GameObject();

	player->box.x = GameData::checkPointX;
	player->box.y = GameData::checkPointY;

	Jogador* jogador = new Jogador(*player, barra_vida);



    Collider* colisor = new Collider(*player);

	
	player->AddComponent(jogador);
    player->AddComponent(colisor);
	
	Camera ::Follow(player);
	objectArray.emplace_back(player);



	GameObject* vida = new GameObject();

	vida->box.x = Camera::GetPos().x; 
	vida->box.y = Camera::GetPos().y - 25; 

	Sprite* info = new Sprite(*vida, "./assets/img/hp_5.png");

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

	Text* info2 = new Text(*estamina, "./assets/font/Abel-Regular.ttf", 50, Text::BLENDED, hud2, SDL_Color{255, 0, 0, 255});

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

	Text* info3 = new Text(*n_item, "./assets/font/Abel-Regular.ttf", 50, Text::BLENDED, hud3, SDL_Color{255, 0, 0, 255});

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
    backgroundMusic = new Music("./assets/audio/Tema_Ambiente.wav");

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

				hp->SetPos(Vec2(Camera::GetPos().x, Camera::GetPos().y));

				    if(GameData::hp_atual == 5){
	    				hp->setTexture("./assets/img/hp_5.png");
    				}
    				else if(GameData::hp_atual == 4){
	    				hp->setTexture("./assets/img/hp_4.png");
    				}
					else if(GameData::hp_atual == 3){
						hp->setTexture("./assets/img/hp_3.png");
					}
					else if(GameData::hp_atual == 2){
						hp->setTexture("./assets/img/hp_2.png");
					}
					else{
						hp->setTexture("./assets/img/hp_1.png");
					}
				///hp->SetText(hud);

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


void StageState:: construirMapa(){


	GameObject* chao = new GameObject();

	Bloco* plataforma = new Bloco(*chao,"./assets/img/plataforma_1.png",360,160, "terra", Vec2(2,2));

	chao->AddComponent(plataforma);
	objectArray.emplace_back(chao);




	GameObject* chao2 = new GameObject();

	Bloco* plataforma2 = new Bloco(*chao2,"./assets/img/plataforma_1.png",1900,100, "terra", Vec2(0.2,1));

	chao2->AddComponent(plataforma2);
	objectArray.emplace_back(chao2);


	GameObject* chao3 = new GameObject();

	Bloco* plataforma3 = new Bloco(*chao3,"./assets/img/plataforma_1.png",2200,100, "terra", Vec2(0.1,10));

	chao3->AddComponent(plataforma3);
	objectArray.emplace_back(chao3);



	GameObject* espinhos1 = new GameObject();

	Bloco* perigo2 = new Bloco(*espinhos1,"./assets/img/espinhos_dr.png",2438,80, "lava", Vec2(1,1));

	espinhos1->AddComponent(perigo2);
	objectArray.emplace_back(espinhos1);


	GameObject* espinhos2 = new GameObject();

	Bloco* perigo3 = new Bloco(*espinhos2,"./assets/img/espinhos_dr.png",2438,-400, "lava", Vec2(1,1));

	espinhos2->AddComponent(perigo3);
	objectArray.emplace_back(espinhos2);



	GameObject* chao4 = new GameObject();

	Bloco* plataforma4 = new Bloco(*chao4,"./assets/img/plataforma_1.png",1850,-730, "terra", Vec2(0.2,6));

	chao4->AddComponent(plataforma4);
	objectArray.emplace_back(chao4);

	

	GameObject* espinhos3 = new GameObject();

	Bloco* perigo4 = new Bloco(*espinhos3,"./assets/img/espinhos_esq.png",2300,-800, "lava", Vec2(1,1));

	espinhos3->AddComponent(perigo4);
	objectArray.emplace_back(espinhos3);

	GameObject* espinhos4 = new GameObject();

	Bloco* perigo5 = new Bloco(*espinhos4,"./assets/img/espinhos_esq.png",2300,-993, "lava", Vec2(1,1));

	espinhos4->AddComponent(perigo5);
	objectArray.emplace_back(espinhos4);


	GameObject* espinhos5 = new GameObject();

	Bloco* perigo6 = new Bloco(*espinhos5,"./assets/img/espinhos_esq.png",2300,-1186, "lava", Vec2(1,1));

	espinhos5->AddComponent(perigo6);
	objectArray.emplace_back(espinhos5);




	GameObject* chao5 = new GameObject();

	Bloco* plataforma5 = new Bloco(*chao5,"./assets/img/plataforma_1.png",2613,-710, "terra", Vec2(1,1));

	chao5->AddComponent(plataforma5);
	objectArray.emplace_back(chao5);




	GameObject* lava = new GameObject();

	Bloco* perigo = new Bloco(*lava,"./assets/img/lava.png",0,300, "lava", Vec2(4,1.2));

	lava->AddComponent(perigo);
	objectArray.emplace_back(lava);

	if(GameData::item == 0){
			GameObject* mascara = new GameObject();

			Bloco* gas_mask = new Bloco(*mascara,"./assets/img/gas_mask_2.png",1000,640, "mascara", Vec2(1,1));

			mascara->AddComponent(gas_mask);
			objectArray.emplace_back(mascara);

	}




	GameObject* checkpoint = new GameObject();

	Bloco* fogueira = new Bloco(*checkpoint,"./assets/img/camp_aceso.png",2635,-765, "checkpoint", Vec2(1,1));

	checkpoint->AddComponent(fogueira);
	objectArray.emplace_back(checkpoint);

/*
	GameObject* checkpoint2 = new GameObject();

	Bloco* fogueira2 = new Bloco(*checkpoint2,"./assets/img/camp_aceso.png",1200,-2, "checkpoint", Vec2(1,1));

	checkpoint2->AddComponent(fogueira2);
	objectArray.emplace_back(checkpoint2);

*/



}