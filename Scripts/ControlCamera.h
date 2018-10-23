//
// Created by kyle on 8/22/18.
//

#ifndef SPACEBOIS_CONTROLCAMERA_H
#define SPACEBOIS_CONTROLCAMERA_H

#include "Component/Component.h"
#include "Component/Camera.h"
#include "GameObject.h"
#include "InputManager.h"

class ControlCamera : public Script {
public:
    ControlCamera(Camera& camera, InputManager& inputManager);

    void start() override {}
    void update() override;
    void end() override {}

    float lookSpeed = 10.0f;
private:
    SBWindow::CursorPos m_lastCursorPos;
    Camera& m_camera;
    InputManager& m_inputManager;

};


#endif //SPACEBOIS_CONTROLCAMERA_H
