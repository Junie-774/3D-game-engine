//
// Created by kyle on 8/23/18.
//

#ifndef SPACEBOIS_GAME_H
#define SPACEBOIS_GAME_H

#include <vector>
#include "GameObject.h"
#include "InputManager.h"
#include "SBWindow.h"

class Game {
public:
    Game();
    void update();

    GameObject::reference addObject(GameObject&& obj);
private:
    //InputManager m_inputManager;
    //SBWindow m_window;

    //std::unordered_map<GameObjectID, GameObject> m_gameObjects;
};


#endif //SPACEBOIS_GAME_H
