//
// Created by kyle on 8/11/18.
//

#ifndef SPACEBOIS_TIME_H
#define SPACEBOIS_TIME_H

#include <memory>
#include <GLFW/glfw3.h>

class Time {
public:
    static Time& instance();

    float deltaTime() const;

    void update();
private:
    Time() = default;

    float m_deltaTime = 0;

    float m_lastTime = 0;
};


#endif //SPACEBOIS_TIME_H
