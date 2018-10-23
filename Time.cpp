//
// Created by kyle on 8/11/18.
//

#include "Time.h"

Time& Time::instance() {
    static std::unique_ptr<Time> instance;

    if (!instance) {
        instance.reset(new Time);
    }

    return *instance;
}

float Time::deltaTime() const {
    return m_deltaTime;
}

void Time::update() {
    auto currTime = static_cast<float>(glfwGetTime());
    m_deltaTime = currTime - m_lastTime;
    m_lastTime = currTime;
}
