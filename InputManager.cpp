//
// Created by kyle on 7/17/18.
//

#include "InputManager.h"

InputManager::InputManager(const SBWindow& window)
:m_window(window),
 m_keyMapping{},
 m_inputeventCommandMapping{},
 m_keyeventCommandMapping{}
{
    m_keyMapping.insert({GLFW_KEY_W, Input::PLAYER_MOVE_FORWARD});
}

void InputManager::fillCommandQueue(std::vector<CommandRef>& toFill) {

    std::vector<Keyboard::KeyEvent> newKeyEvents;
    m_window.getKeyboard().fillEventQueue(newKeyEvents);

    for (auto& kEvent : newKeyEvents) {

        if (m_keyMapping.count(kEvent.first) > 0) {

            auto inEvent = std::pair(m_keyMapping.at(kEvent.first), kEvent.second);
            auto commandPairs = m_inputeventCommandMapping.equal_range(inEvent);
            for (auto itr = commandPairs.first; itr != commandPairs.second; itr++) {
                toFill.push_back(itr->second);
            }
        }

        auto commandPairs = m_keyeventCommandMapping.equal_range(kEvent);
        for (auto itr = commandPairs.first; itr != commandPairs.second; itr++) {
            toFill.push_back(itr->second);
        }

    }

}


void InputManager::assignCommandToInputEvent(InputEvent event, CommandRef cmd) {
    m_inputeventCommandMapping.insert({event, cmd});
}

void InputManager::assignCommandToKeyEvent(Keyboard::KeyEvent event, CommandRef cmd) {
    m_keyeventCommandMapping.insert({event, cmd});
}

void InputManager::mapKeyToInput(Keyboard::Key key, Input input) {
    m_keyMapping.insert( {key, input} );
}

bool InputManager::isKeyDown(Keyboard::Key key) const {
    return m_window.getKeyboard().isKeyDown(key);
}

SBWindow::CursorPos InputManager::getCursorPos() const {
    return m_window.getCursorPos();
}


