#include "../include/tileset.h"


// cria um tileset n esta sendo usado no momento

TileSet :: TileSet (int tileWidth, int tileHeight, std::string file) : tileSet(*(new GameObject()), file){



    this->tileHeight = tileHeight;
    this->tileWidth = tileWidth;
    


    int altura = tileSet.GetHeight();
    int largura = tileSet.GetWidth();
    
    columns = largura/tileWidth;
    rows = altura/tileHeight;


}


void TileSet :: RenderTile (unsigned index, float x, float y) {

    int indy = (index/columns) * tileHeight;
    int indx = (index%columns)  * tileWidth;

    if((index >=0) and (index <= (columns*rows)-1)){
        tileSet.SetClip(indx,indy,tileWidth,tileHeight);
        tileSet.Render(x,y);


    };






}


int TileSet :: GetTileWidth (){

    return tileWidth;

}



int TileSet :: GetTileHeight(){

    return tileHeight;

}