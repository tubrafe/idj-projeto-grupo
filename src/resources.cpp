#include "../include/resources.h"
#include <string>
#include "../include/game.h"

std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources :: soundTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources :: musicTable;
std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources :: imageTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources :: fontTable;

std::shared_ptr<SDL_Texture> Resources :: GetImage(std::string file ){

    if(imageTable.find(file) != imageTable.end() ){

        return imageTable[file] ;


    }

    const char * c = file.c_str();
    SDL_Texture* temp = IMG_LoadTexture(Game :: GetInstance ().GetRenderer(), c );
    if(temp != nullptr){
        imageTable[file] = std::shared_ptr<SDL_Texture>(temp,[](SDL_Texture* ptr){SDL_DestroyTexture(ptr);});

        return imageTable[file];
    }
    
    return nullptr;

}





void Resources :: ClearImage() {


    for(auto i = imageTable.begin();i != imageTable.end();i++){

        if(i->second.unique() == true){
            imageTable.erase(i);        
        }

    }

}




std::shared_ptr<Mix_Music> Resources :: GetMusic(std::string file) {

    if(musicTable.find(file) != musicTable.end() ){

        return musicTable[file] ;


    }

    const char * c = file.c_str();
    Mix_Music* temp = Mix_LoadMUS(c); 

    if(temp!=nullptr){

        musicTable[file] = std::shared_ptr<Mix_Music>(temp,[](Mix_Music* ptr){Mix_FreeMusic(ptr);});
        return musicTable[file];
    }

    return nullptr;


}



void Resources :: ClearMusic() {

    for(auto i = musicTable.begin();i != musicTable.end();i++){

        if(i->second.unique() == true){
            musicTable.erase(i);        
        }

    }


}




std::shared_ptr<Mix_Chunk> Resources :: GetSound(std::string file) {


    if(soundTable.find(file) != soundTable.end() ){

        return soundTable[file] ;


    }


    const char * c = file.c_str();
    Mix_Chunk* temp = Mix_LoadWAV(c);

    if(temp!=nullptr){

        soundTable[file] = std::shared_ptr<Mix_Chunk>(temp,[](Mix_Chunk* ptr){Mix_FreeChunk(ptr);});;
        return soundTable[file];
    }

   return nullptr; 


}




void Resources :: ClearSounds() {

    for(auto i = soundTable.begin();i != soundTable.end();i++){

        if(i->second.unique() == true){
            soundTable.erase(i);        
        }

    }




}



std::shared_ptr<TTF_Font> Resources :: GetFont(std::string file, int size){

    if(fontTable.find(file+std::to_string(size)) != fontTable.end() ){

        return fontTable[file+std::to_string(size)] ;


    }

    const char * c = file.c_str();
    TTF_Font* temp = TTF_OpenFont(c, size);

    if(temp != nullptr){
        fontTable[file+std::to_string(size)] = std::shared_ptr<TTF_Font>(temp,[](TTF_Font* ptr){TTF_CloseFont(ptr);});

        return fontTable[file+std::to_string(size)];
    }

    return nullptr;

}


void Resources :: ClearFont() {

    for(auto i = fontTable.begin();i != fontTable.end();i++){

        if(i->second.unique() == true){
            fontTable.erase(i);        
        }

    }




}