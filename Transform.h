#ifndef TRANSFORM_H
#define TRANSFORM_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

class Transform
{
public:
    explicit Transform(glm::vec3 initPos = glm::vec3(0.0f, 0.0f, 0.0f),
              glm::vec3 initScale = glm::vec3(1.0f, 1.0f, 1.0f));



    glm::vec3 position() const;
    glm::vec3 rotation() const;
    glm::vec3 scale() const;

    void setPosition(glm::vec3 newPos);
    void setRotation(float newAngle, glm::vec3 newAxis);
    void setScale(glm::vec3 newScale);

    void translate(glm::vec3 deltaPos);
    void rotate(float deltaAngle, glm::vec3 axis);
    void scale(glm::vec3 deltaScale);

    glm::mat4 model() const;

private:
    // store info outside of the model matrix for to use later
    glm::vec3 m_position;
    glm::vec3 m_scale;
    glm::quat m_orientation;


};

#endif // TRANSFORM_H
