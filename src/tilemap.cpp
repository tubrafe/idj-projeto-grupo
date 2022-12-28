#include "../include/camera.h"
#include "../include/tilemap.h"
#include <fstream>
#include <sstream>

// cria um tilemap n esta sendo usado no momento

TileMap :: TileMap(GameObject& associated, std::string file , TileSet* tileSet): Component(associated){

    Load(file);
    this->tileSet = tileSet;
  
}



void TileMap :: Load(std::string file){

    FILE* arquivo;
    const char * c = file.c_str();
    arquivo = fopen(c,"r");
    int aux;

    fscanf(arquivo,"%d,%d,%d,\n\n", &mapWidth,&mapHeight,&mapDepth);
    int i,j,k;

    for (i=0;i<mapDepth;i++){

        for(j=0;j<mapHeight;j++){

            for(k=0;k<mapWidth;k++){

                fscanf(arquivo,"%d,", &aux);
                aux = aux - 1;
                tileMatrix.push_back(aux);


            }
            fscanf(arquivo,"\n");



        }
        fscanf(arquivo,"\n");



    }


}



void TileMap :: SetTileSet(TileSet* tileSet){


    this->tileSet = tileSet; 



}



int& TileMap :: At(int x, int y, int z){

    int valor;
    int ind;

    ind = (z*mapWidth*mapHeight) + (x*mapWidth) + y;

    return tileMatrix[ind];

}




void TileMap :: RenderLayer(int layer, float cameraX, float cameraY){


    int i,j;

    for (i=0;i<mapWidth;i++){
        for (j=0;j<mapHeight;j++){

            tileSet->RenderTile(At(j,i,layer),((tileSet->GetTileWidth())*i - cameraX),((tileSet->GetTileHeight())*j- cameraY));
        }

    }


}



void TileMap :: Render(){

    int i;
    for(i=0;i<mapDepth;i++){
        RenderLayer(i,Camera :: pos.x,Camera :: pos.y);

    }



}




int TileMap :: GetWidth(){

    return mapWidth;

}

int TileMap :: GetHeight(){

    return mapHeight;


}

int TileMap :: GetDepth(){

    return mapDepth;

}



void TileMap :: Update(float dt){}


bool TileMap :: Is(std :: string type){

    if(type == "tilemap"){
        return true;
    };
    return false;


}