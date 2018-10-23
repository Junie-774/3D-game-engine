//
// Created by kyle on 9/2/18.
//

#include "Keyboard.h"
#include <iostream>

void Keyboard::fillEventQueue(std::vector<Keyboard::KeyEvent>& toFill) const {

    toFill.insert(toFill.end(), m_newEvents.begin(), m_newEvents.end());
    m_newEvents.clear();

    for (auto& i : m_pressedKeys) {
        toFill.emplace_back(i, KeyAction::HOLD);
    }
}

bool Keyboard::isKeyDown(Keyboard::Key key) const {

    return m_keyStates.at(static_cast<unsigned long>(key)) == KeyState::DOWN;
}

void Keyboard::keyDown(Key k) {

    m_pressedKeys.insert(k);
    m_keyStates.at(static_cast<decltype(m_keyStates)::size_type>(k)) = KeyState::DOWN;
    m_newEvents.emplace_back(k, KeyAction::PRESS);
}

void Keyboard::keyUp(Keyboard::Key k) {

    m_pressedKeys.erase(k);
    m_keyStates.at(static_cast<decltype(m_keyStates)::size_type>(k)) = KeyState::UP;
    m_newEvents.emplace_back(k, KeyAction::RELEASE);
}

void Keyboard::keyCallback(Key key, int action) {

    switch (action) {
        case GLFW_PRESS:
            keyDown(key);
            break;
        case GLFW_RELEASE:
            keyUp(key);
            break;
        default:
            break;
    }
}