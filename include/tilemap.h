#ifndef TILEMAP_H
#define TILEMAP_H


#include <iostream>
#include <vector>
#include "component.h"
#include "tileset.h"

class GameObject;

class TileMap : public Component {

    public:
        TileMap(GameObject& associated, std::string , TileSet* tileSet);
        void Load(std::string file);
        void SetTileSet(TileSet* tileSet);
        int& At(int x, int y, int z = 0);
        void Render();
        void RenderLayer(int layer, float cameraX, float cameraY);
        int GetWidth();
        int GetHeight();
        int GetDepth();
        
        void Update(float dt);
        bool Is(std :: string type);


    private:
        std::vector<int> tileMatrix;
        TileSet* tileSet;
        int mapWidth;
        int mapHeight; 
        int mapDepth;

};












#endif