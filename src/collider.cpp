#include "../include/collider.h"
#include "../include/state.h"


// Adicione o trecho abaixo no começo do seu Collider.cpp,
// logo após os seus includes e antes de qualquer função.

#ifdef DEBUG
#include "../include/camera.h"
#include "../include/game.h"

#include <SDL2/SDL.h>
#endif // DEBUG





// Copie o conteúdo dessa função para dentro da sua e adapte o nome das funções para as suas.
// Funções usadas:
// Rect::GetCenter()				- Retorna um Vec2 no centro do Rect
// Vec2::operator-( const Vec2& )	- Subtrai dois Vec2
// Vec2::Rotate( float rad )		- Rotaciona um Vec2 pelo ângulo em radianos passado
void Collider::Render() {
#ifdef DEBUG
	Vec2 center( box.GetCenter() );
	SDL_Point points[5];

	Vec2 point = (center - Vec2(box.x, box.y)).GetRotated( associated.angleDeg/(180/M_PI) )
					+ Camera::pos - center ;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (center - Vec2(box.x + box.w, box.y)).GetRotated( associated.angleDeg/(180/M_PI) )
					+ Camera::pos - center ;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (center - Vec2(box.x + box.w, box.y + box.h)).GetRotated( associated.angleDeg/(180/M_PI) )
					+ Camera::pos - center ;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (center - Vec2(box.x, box.y + box.h)).GetRotated( associated.angleDeg/(180/M_PI) )
					+ Camera::pos - center ;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}




Collider :: Collider(GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated){

    this->scale = scale;
    this->offset = offset;



}



void Collider :: Update (float dt){


    box.x = associated.box.x;
    box.y = associated.box.y;



    box.h = associated.box.h * scale.y;
    box.w = associated.box.w * scale.x;

    float angulo = associated.angleDeg * (M_PI/180);

    Vec2 temp = offset.GetRotated(angulo);

    box.x = (box.GetCenter().x + temp.x) - box.w/2;
    box.y = (box.GetCenter().y + temp.y) - box.h/2;

    printf("%f colisor\n", box.y+box.h);

}









bool Collider :: Is (std::string type){


    if (type == "collider"){
        return true;
    };
    return false;



}


void Collider :: SetScale (Vec2 scale){


    this->scale = scale;



}
 
 
 
void Collider :: SetOffset (Vec2 offset){


    this->offset = offset;



}



bool Collider :: IsColliding(Collider colisor){

    float angulo_go = associated.angleDeg * (M_PI/180);
    float angulo_co = colisor.associated.angleDeg * (M_PI/180);

    Rect box_co = colisor.box;

    bool resposta = Collision :: IsColliding(box,box_co,angulo_go,angulo_co);


    return resposta;


}