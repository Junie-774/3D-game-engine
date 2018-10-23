//
// Created by kyle on 8/21/18.
//

#ifndef SPACEBOIS_PLAYERMOVEMENT_H
#define SPACEBOIS_PLAYERMOVEMENT_H

#include <InputManager.h>
#include <Scripts/Script.h>
#include <Time.h>
#include "Component/Camera.h"

class Player;

class PlayerMovement : public Script {

public:
    PlayerMovement(GameObject& player, InputManager& inputManager);

    void start() override;
    void update() override;
    void end() override;

private:
    GameObject& m_player;
    Camera& m_camera;
    InputManager& m_inputManager;

    float m_speed = 1.0;
};


#endif //SPACEBOIS_PLAYERMOVEMENT_H
