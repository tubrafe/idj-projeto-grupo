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

	std::getline(save, linha);
	GameData::garra = std::stoi(linha);


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
	vida->box.y = Camera::GetPos().y; 

	Sprite* info = new Sprite(*vida, "./assets/img/hp_5.png");

	hp = info;

	vida->AddComponent(info);
	objectArray.emplace_back(vida);



	GameObject* estamina = new GameObject();





	estamina->box.x = Camera::GetPos().x; 
	estamina->box.y = Camera::GetPos().y + 50; 

	Sprite* info2 = new Sprite(*estamina, "./assets/img/stamina_9");

	stamina = info2;

	estamina->AddComponent(info2);
	objectArray.emplace_back(estamina);






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
			salvar.append("\n");
			salvar.append(std::to_string(GameData::garra));


			save << salvar << endl;
			save.close();

        GameData::playerVictory = false;
        popRequested = true;
		EndState* fim = new EndState();
        Game::GetInstance().Push(fim);

    }

	else if (GameData::playerVictory == true){
			GameData::checkPointX = 0;
			GameData::checkPointY = 0;
			GameData::garra = 0;
			GameData::item = 0;
			GameData::hp_atual = 5;
			std::ofstream save ("./assets/save/save.txt"); 
			std::string salvar = std::to_string(GameData::checkPointX);
			salvar.append("\n");
			salvar.append(std::to_string(GameData::checkPointY));
			salvar.append("\n");
			salvar.append(std::to_string(GameData::hp_atual));
			salvar.append("\n");
			salvar.append(std::to_string(GameData::item));
			salvar.append("\n");
			salvar.append(std::to_string(GameData::garra));


			save << salvar << endl;
			save.close();
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
			salvar.append("\n");
			salvar.append(std::to_string(GameData::garra));
			

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

				stamina->SetPos(Vec2(Camera::GetPos().x, Camera::GetPos().y + 50));

				    if(GameData::stamina_atual == 5){
	    				stamina->setTexture("./assets/img/stamina_10.png");
    				}
    				else if(GameData::stamina_atual == 4.5){
	    				stamina->setTexture("./assets/img/stamina_9.png");
    				}
					else if(GameData::stamina_atual == 4){
						stamina->setTexture("./assets/img/stamina_8.png");
					}
					else if(GameData::stamina_atual == 3.5){
						stamina->setTexture("./assets/img/stamina_7.png");
					}
					else if(GameData::stamina_atual == 3){
						stamina->setTexture("./assets/img/stamina_6.png");
					}

				    else if(GameData::stamina_atual == 2.5){
	    				stamina->setTexture("./assets/img/stamina_5.png");
    				}
    				else if(GameData::stamina_atual == 2){
	    				stamina->setTexture("./assets/img/stamina_4.png");
    				}
					else if(GameData::stamina_atual == 1.5){
						stamina->setTexture("./assets/img/stamina_3.png");
					}
					else if(GameData::stamina_atual == 1){
						stamina->setTexture("./assets/img/stamina_2.png");
					}
					else if(GameData::stamina_atual == 0.5){
						stamina->setTexture("./assets/img/stamina_1.png");
					}
					else{
						stamina->setTexture("./assets/img/stamina_0.png");						
					}



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

	Bloco* plataforma3 = new Bloco(*chao3,"./assets/img/plataforma_1.png",2238,100, "terra", Vec2(0.2,10));

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

	Bloco* plataforma5 = new Bloco(*chao5,"./assets/img/plataforma_1.png",2688,-710, "terra", Vec2(1,1));

	chao5->AddComponent(plataforma5);
	objectArray.emplace_back(chao5);




	GameObject* chao6 = new GameObject();

	Bloco* plataforma6 = new Bloco(*chao6,"./assets/img/plataforma_1.png",2613,-1200, "terra", Vec2(1,1));

	chao6->AddComponent(plataforma6);
	objectArray.emplace_back(chao6);


	GameObject* chao7 = new GameObject();

	Bloco* plataforma7 = new Bloco(*chao7,"./assets/img/plataforma_1.png",3215,-1200, "terra", Vec2(0.6,1));

	chao7->AddComponent(plataforma7);
	objectArray.emplace_back(chao7);


	GameObject* chao8 = new GameObject();

	Bloco* plataforma8 = new Bloco(*chao8,"./assets/img/plataforma_1.png",3475,-730, "terra", Vec2(0.2,6));

	chao8->AddComponent(plataforma8);
	objectArray.emplace_back(chao8);


	GameObject* espinhos6 = new GameObject();

	Bloco* perigo7 = new Bloco(*espinhos6,"./assets/img/espinhos_dr.png",3675,-1017, "lava", Vec2(1,1));

	espinhos6->AddComponent(perigo7);
	objectArray.emplace_back(espinhos6);


	GameObject* espinhos7 = new GameObject();

	Bloco* perigo8 = new Bloco(*espinhos7,"./assets/img/espinhos_dr.png",3675,-824, "lava", Vec2(1,1));

	espinhos7->AddComponent(perigo8);
	objectArray.emplace_back(espinhos7);


	GameObject* chao9 = new GameObject();

	Bloco* plataforma9 = new Bloco(*chao9,"./assets/img/plataforma_1.png",3025,-282, "terra", Vec2(1,1));

	chao9->AddComponent(plataforma9);
	objectArray.emplace_back(chao9);


	GameObject* espinhos8 = new GameObject();

	Bloco* perigo9 = new Bloco(*espinhos8,"./assets/img/espinhos_up.png",3580,-382, "lava", Vec2(1,1));

	espinhos8->AddComponent(perigo9);
	objectArray.emplace_back(espinhos8);


	GameObject* espinhos9 = new GameObject();

	Bloco* perigo10 = new Bloco(*espinhos9,"./assets/img/espinhos_up.png",3387,-382, "lava", Vec2(1,1));

	espinhos9->AddComponent(perigo10);
	objectArray.emplace_back(espinhos9);


	GameObject* espinhos10 = new GameObject();

	Bloco* perigo11 = new Bloco(*espinhos10,"./assets/img/espinhos_esq.png",2689,-527, "lava", Vec2(1,1));

	espinhos10->AddComponent(perigo11);
	objectArray.emplace_back(espinhos10);




	GameObject* espinhos11 = new GameObject();

	Bloco* perigo12 = new Bloco(*espinhos11,"./assets/img/espinhos_esq.png",2689,-187, "lava", Vec2(1,1));

	espinhos11->AddComponent(perigo12);
	objectArray.emplace_back(espinhos11);




	GameObject* chao10 = new GameObject();

	Bloco* plataforma10 = new Bloco(*chao10,"./assets/img/plataforma_1.png",2688,100, "terra", Vec2(1,1));

	chao10->AddComponent(plataforma10);
	objectArray.emplace_back(chao10);


	GameObject* espinhos12 = new GameObject();

	Bloco* perigo13 = new Bloco(*espinhos12,"./assets/img/espinhos_up.png",2750,0, "lava", Vec2(1,1));

	espinhos12->AddComponent(perigo13);
	objectArray.emplace_back(espinhos12);



	GameObject* chao11 = new GameObject();

	Bloco* plataforma11 = new Bloco(*chao11,"./assets/img/plataforma_1.png",3900,100, "terra", Vec2(1,1));

	chao11->AddComponent(plataforma11);
	objectArray.emplace_back(chao11);







	if(GameData::item == 0){
			GameObject* mascara = new GameObject();

			Bloco* gas_mask = new Bloco(*mascara,"./assets/img/gas_mask_2.png",1000,640, "mascara", Vec2(1,1));

			mascara->AddComponent(gas_mask);
			objectArray.emplace_back(mascara);

	}




	GameObject* checkpoint = new GameObject();

	Bloco* fogueira = new Bloco(*checkpoint,"./assets/img/camp_aceso.png",2635,-832, "checkpoint", Vec2(1,1));

	checkpoint->AddComponent(fogueira);
	objectArray.emplace_back(checkpoint);


	GameObject* checkpoint2 = new GameObject();

	Bloco* fogueira2 = new Bloco(*checkpoint2,"./assets/img/camp_aceso.png",4110,-22, "checkpoint", Vec2(1,1));

	checkpoint2->AddComponent(fogueira2);
	objectArray.emplace_back(checkpoint2);





	GameObject* chao12 = new GameObject();

	Bloco* plataforma12 = new Bloco(*chao12,"./assets/img/plataforma_1.png",5100,100, "terra", Vec2(0.2,1));

	chao12->AddComponent(plataforma12);
	objectArray.emplace_back(chao12);




	GameObject* chao13 = new GameObject();

	Bloco* plataforma13 = new Bloco(*chao13,"./assets/img/plataforma_1.png",6300,100, "terra", Vec2(1,1));

	chao13->AddComponent(plataforma13);
	objectArray.emplace_back(chao13);


	GameObject* chao14 = new GameObject();

	Bloco* plataforma14 = new Bloco(*chao14,"./assets/img/plataforma_1.png",7205,100, "terra", Vec2(1,1));

	chao14->AddComponent(plataforma14);
	objectArray.emplace_back(chao14);



	GameObject* chao15 = new GameObject();

	Bloco* plataforma15 = new Bloco(*chao15,"./assets/img/plataforma_1.png",6300,-270, "terra", Vec2(1,1));

	chao15->AddComponent(plataforma15);
	objectArray.emplace_back(chao15);



	GameObject* chao16 = new GameObject();

	Bloco* plataforma16 = new Bloco(*chao16,"./assets/img/plataforma_1.png",7050,-270, "terra", Vec2(1,1));

	chao16->AddComponent(plataforma16);
	objectArray.emplace_back(chao16);



	GameObject* espinhos14 = new GameObject();

	Bloco* perigo15 = new Bloco(*espinhos14,"./assets/img/espinhos_down.png",7050,-90, "lava", Vec2(1,1));

	espinhos14->AddComponent(perigo15);
	objectArray.emplace_back(espinhos14);


	GameObject* espinhos15 = new GameObject();

	Bloco* perigo16 = new Bloco(*espinhos15,"./assets/img/espinhos_down.png",6857,-90, "lava", Vec2(1,1));

	espinhos15->AddComponent(perigo16);
	objectArray.emplace_back(espinhos15);


	GameObject* espinhos16 = new GameObject();

	Bloco* perigo17 = new Bloco(*espinhos16,"./assets/img/espinhos_down.png",6664,-90, "lava", Vec2(1,1));

	espinhos16->AddComponent(perigo17);
	objectArray.emplace_back(espinhos16);


	GameObject* espinhos17 = new GameObject();

	Bloco* perigo18 = new Bloco(*espinhos17,"./assets/img/espinhos_down.png",6471,-90, "lava", Vec2(1,1));

	espinhos17->AddComponent(perigo18);
	objectArray.emplace_back(espinhos17);


	GameObject* espinhos18 = new GameObject();

	Bloco* perigo19 = new Bloco(*espinhos18,"./assets/img/espinhos_down.png",7243,-90, "lava", Vec2(1,1));

	espinhos18->AddComponent(perigo19);
	objectArray.emplace_back(espinhos18);


	GameObject* espinhos19 = new GameObject();

	Bloco* perigo20 = new Bloco(*espinhos19,"./assets/img/espinhos_down.png",7436,-90, "lava", Vec2(1,1));

	espinhos19->AddComponent(perigo20);
	objectArray.emplace_back(espinhos19);




	GameObject* chao17 = new GameObject();

	Bloco* plataforma17 = new Bloco(*chao17,"./assets/img/plataforma_1.png",7800,100, "terra", Vec2(0.2,1));

	chao17->AddComponent(plataforma17);
	objectArray.emplace_back(chao17);



	GameObject* espinhos20 = new GameObject();

	Bloco* perigo21 = new Bloco(*espinhos20,"./assets/img/espinhos_up.png",8078,20, "lava", Vec2(0.8,0.8));

	espinhos20->AddComponent(perigo21);
	objectArray.emplace_back(espinhos20);




	GameObject* chao18 = new GameObject();

	Bloco* plataforma18 = new Bloco(*chao18,"./assets/img/plataforma_1.png",8400,100, "terra", Vec2(1,1));

	chao18->AddComponent(plataforma18);
	objectArray.emplace_back(chao18);



	GameObject* chao19 = new GameObject();

	Bloco* plataforma19 = new Bloco(*chao19,"./assets/img/plataforma_1.png",8400,-270, "terra", Vec2(1,1));

	chao19->AddComponent(plataforma19);
	objectArray.emplace_back(chao19);


	GameObject* espinhos21 = new GameObject();

	Bloco* perigo22 = new Bloco(*espinhos21,"./assets/img/espinhos_down.png",8500,-90, "lava", Vec2(1,1));

	espinhos21->AddComponent(perigo22);
	objectArray.emplace_back(espinhos21);




	GameObject* espinhos22 = new GameObject();

	Bloco* perigo23 = new Bloco(*espinhos22,"./assets/img/espinhos_up.png",8800, 20, "lava", Vec2(1,0.6));

	espinhos22->AddComponent(perigo23);
	objectArray.emplace_back(espinhos22);



	GameObject* mola = new GameObject();

	Bloco* pulo = new Bloco(*mola,"./assets/img/mola.png",9500, -20, "mola", Vec2(1,1));

	mola->AddComponent(pulo);
	objectArray.emplace_back(mola);



	GameObject* mola2 = new GameObject();

	Bloco* pulo2 = new Bloco(*mola2,"./assets/img/mola.png",10000, -40, "mola", Vec2(1,1));

	mola2->AddComponent(pulo2);
	objectArray.emplace_back(mola2);




	GameObject* chao20 = new GameObject();

	Bloco* plataforma20 = new Bloco(*chao20,"./assets/img/plataforma_1.png",10400,100, "terra", Vec2(1,1));

	chao20->AddComponent(plataforma20);
	objectArray.emplace_back(chao20);



	GameObject* checkpoint3 = new GameObject();
	Bloco* fogueira3 = new Bloco(*checkpoint3,"./assets/img/camp_aceso.png",10500,-25 , "checkpoint", Vec2(1,1));

	checkpoint3->AddComponent(fogueira3);
	objectArray.emplace_back(checkpoint3);



	GameObject* bloco_final = new GameObject();
	Bloco* vitoria = new Bloco(*bloco_final,"./assets/img/camp_aceso.png",10800,-25 , "vitoria", Vec2(1,1));

	bloco_final->AddComponent(vitoria);
	objectArray.emplace_back(bloco_final);





//continuar?












	GameObject* gas = new GameObject();

	Bloco* veneno = new Bloco(*gas,"./assets/img/nevoa.png",2250,-20, "gas", Vec2(2,10));

	gas->AddComponent(veneno);
	objectArray.emplace_back(gas);


	GameObject* piso1 = new GameObject();

	Bloco* passarela1 = new Bloco(*piso1,"./assets/img/plataforma_1.png",-1400,100, "terra", Vec2(1,1));

	piso1->AddComponent(passarela1);
	objectArray.emplace_back(piso1);

	GameObject* piso2 = new GameObject();

	Bloco* passarela2 = new Bloco(*piso2,"./assets/img/plataforma_1.png",-1200,-180, "terra", Vec2(0.15,0.5));

	piso2->AddComponent(passarela2);
	objectArray.emplace_back(piso2);

	GameObject* piso3 = new GameObject();

	Bloco* passarela3 = new Bloco(*piso3,"./assets/img/plataforma_1.png",-1600,-320, "terra", Vec2(0.175,0.5));

	piso3->AddComponent(passarela3);
	objectArray.emplace_back(piso3);

	GameObject* piso4 = new GameObject();

	Bloco* passarela4 = new Bloco(*piso4,"./assets/img/plataforma_1.png",-900,-500, "terra", Vec2(0.3,0.6));

	piso4->AddComponent(passarela4);
	objectArray.emplace_back(piso4);

	GameObject* piso5 = new GameObject();

	Bloco* passarela5 = new Bloco(*piso5,"./assets/img/plataforma_1.png",-300,-700, "terra", Vec2(0.8,0.5));

	piso5->AddComponent(passarela5);
	objectArray.emplace_back(piso5);

	GameObject* piso6 = new GameObject();

	Bloco* passarela6 = new Bloco(*piso6,"./assets/img/plataforma_1.png",-2300,100, "terra", Vec2(1,1));

	piso6->AddComponent(passarela6);
	objectArray.emplace_back(piso6);



	GameObject* piso7 = new GameObject();

	Bloco* passarela7 = new Bloco(*piso7,"./assets/img/plataforma_1.png",-2900,100, "terra", Vec2(0.175,1));

	piso7->AddComponent(passarela7);
	objectArray.emplace_back(piso7);

	GameObject* piso8 = new GameObject();

	Bloco* passarela8 = new Bloco(*piso8,"./assets/img/plataforma_1.png",-3300,100, "terra", Vec2(0.175,1));

	piso8->AddComponent(passarela8);
	objectArray.emplace_back(piso8);



	GameObject* piso9 = new GameObject();

	Bloco* passarela9 = new Bloco(*piso9,"./assets/img/plataforma_1.png",-3600,100, "terra", Vec2(0.15,0.5));

	piso9->AddComponent(passarela9);
	objectArray.emplace_back(piso9);



	GameObject* piso10 = new GameObject();

	Bloco* passarela10 = new Bloco(*piso10,"./assets/img/plataforma_1.png",-4700,100, "terra", Vec2(2,1));

	piso10->AddComponent(passarela10);
	objectArray.emplace_back(piso10);


	GameObject* piso11 = new GameObject();

	Bloco* passarela11 = new Bloco(*piso11,"./assets/img/plataforma_1.png",-5600,100, "terra", Vec2(2,1));

	piso11->AddComponent(passarela11);
	objectArray.emplace_back(piso11);

	GameObject* spike1 = new GameObject();

	Bloco* peligro1 = new Bloco(*spike1,"./assets/img/espinhos_up.png",-4300,25, "lava", Vec2(0.65,0.5));

	spike1->AddComponent(peligro1);
	objectArray.emplace_back(spike1);


	GameObject* spike2 = new GameObject();

	Bloco* peligro2 = new Bloco(*spike2,"./assets/img/espinhos_up.png",-4400,25, "lava", Vec2(0.65,0.5));

	spike2->AddComponent(peligro2);
	objectArray.emplace_back(spike2);

	
	GameObject* spike3 = new GameObject();

	Bloco* peligro3 = new Bloco(*spike3,"./assets/img/espinhos_up.png",-4630,20, "lava", Vec2(0.7,0.6));

	spike3->AddComponent(peligro3);
	objectArray.emplace_back(spike3);

	GameObject* spike4 = new GameObject();

	Bloco* peligro4 = new Bloco(*spike4,"./assets/img/espinhos_up.png",-5000,20, "lava", Vec2(0.7,0.6));

	spike4->AddComponent(peligro4);
	objectArray.emplace_back(spike4);






	GameObject* saojoao = new GameObject();

	Bloco* bonfire = new Bloco(*saojoao,"./assets/img/camp_aceso.png",-3800,-20, "checkpoint", Vec2(1,1));

	saojoao->AddComponent(bonfire);
	objectArray.emplace_back(saojoao);

	GameObject* saojoao1 = new GameObject();

	Bloco* bonfire1 = new Bloco(*saojoao1,"./assets/img/camp_aceso.png",0,-50, "checkpoint", Vec2(1,1));

	saojoao1->AddComponent(bonfire1);
	objectArray.emplace_back(saojoao1);


	//############   PLACA       ###########################
 



	if(GameData::item == 0){
			GameObject* mascara = new GameObject();

			Bloco* gas_mask = new Bloco(*mascara,"./assets/img/gas_mask_2.png",200,-700, "mascara", Vec2(1,1));

			mascara->AddComponent(gas_mask);
			objectArray.emplace_back(mascara);

	}


	if(GameData::garra == 0){
			GameObject* garra_item = new GameObject();

			Bloco* claw = new Bloco(*garra_item,"./assets/img/garra.png",-5900,0, "garra", Vec2(0.7,0.7));

			garra_item->AddComponent(claw);
			objectArray.emplace_back(garra_item);

	}

	GameObject* lava3 = new GameObject();

	Bloco* danger3 = new Bloco(*lava3,"./assets/img/lava.png",-7408,250, "lava", Vec2(1,1));

	lava3->AddComponent(danger3);
	objectArray.emplace_back(lava3);

	GameObject* lava4 = new GameObject();

	Bloco* danger4 = new Bloco(*lava4,"./assets/img/lava.png",-14816,250, "lava", Vec2(1,1));

	lava4->AddComponent(danger4);
	objectArray.emplace_back(lava4);


	GameObject* lava = new GameObject();

	Bloco* perigo = new Bloco(*lava,"./assets/img/lava.png",0,250, "lava", Vec2(1,1));

	lava->AddComponent(perigo);
	objectArray.emplace_back(lava);

	GameObject* lava2 = new GameObject();

	Bloco* perigo14 = new Bloco(*lava2,"./assets/img/lava.png",7408,250, "lava", Vec2(1,1));

	lava2->AddComponent(perigo14);
	objectArray.emplace_back(lava2);

}