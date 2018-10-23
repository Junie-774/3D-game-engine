//
// Created by kyle on 8/8/18.
//

#ifndef SPACEBOIS_CAMERA_H
#define SPACEBOIS_CAMERA_H

#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Component/Component.h"
#include "GameObject.h"

static glm::vec3 projectToXZ(glm::vec3 vec) {
    return glm::vec3(vec.x, 0.0f, vec.z);
}

static glm::vec3 projectToXY(glm::vec3 vec) {
    return glm::vec3(vec.x, vec.y, 0.0f);
}

static glm::vec3 projectToYZ(glm::vec3 vec) {
    return glm::vec3(0.0f, vec.y, vec.z);
}

static glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

class Camera : public Component {
    constexpr static float MAX_PITCH = 89.0f;
    constexpr static float clipPitch(float pitch);

public:

    static constexpr auto TYPE = "Camera";
    const std::string type() const override { return Camera::TYPE; }
    explicit Camera(GameObject& parent, float yaw = 0.0f, float pitch = 0.0f);


    constexpr auto front() const { return m_frontDirection; };
    constexpr auto right() const { return m_rightDirection; };
    constexpr auto yaw() const { return m_yaw; }
    constexpr auto pitch() const { return m_pitch; }

    void rotateDegrees(float deltaYaw, float deltaPitch);
    void rotateRads(float deltaYaw, float deltaPitch);
    void lookAt(glm::vec3 target);

    glm::mat4 getViewMat() const;

private:

    /**
     * Camera::getVectorFromAngles(float, float)
     *
     * Takes a yaw and a pitch to get the vector pointing in that direction. Primarily for updating
     * m_frontDirection
     *
     * @param yaw Rotation around the Y-axis (left/right), in radians
     * @param pitch Rotation around the X-axis (up/down), in radians
     *
     * @return A vector pointing in the direction denoted by yaw and pitch, length is unspecified
     */
    static glm::vec3 getVectorFromAngles(float yaw, float pitch);
    float m_yaw;
    float m_pitch;

    glm::vec3 m_frontDirection; // Direction camera is facing
    glm::vec3 m_rightDirection; // To the right of the camera
    glm::vec3 m_upDirection; // Orientation of the camera, should be orthogonal to m_lookDirection

    void updateVectors(glm::vec3 newFront);

};


#endif //SPACEBOIS_CAMERA_H
