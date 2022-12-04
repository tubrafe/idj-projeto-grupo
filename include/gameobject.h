#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <iostream>
#include <vector>
#include <memory>
#define INCLUDE_SDL
#include "SDL_include.h"
#include "rect.h"

class Component;

class GameObject{

    public:
        GameObject();
        ~GameObject();
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(std::string type);
        Rect box;
        void Start();
        bool started;

        double angleDeg;

        void NotifyCollision (GameObject& other);

    private:
        std::vector<std::unique_ptr<Component>> components;
        bool isDead;


};


#endif