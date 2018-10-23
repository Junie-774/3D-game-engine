//
// Created by kyle on 7/17/18.
//

#ifndef SPACEBOIS_INPUTMANAGER_H
#define SPACEBOIS_INPUTMANAGER_H

#include <array>
#include <iostream>
#include <unordered_map>
#include <map>
#include <GLFW/glfw3.h>
#include "Command.h"
#include "Keyboard.h"
#include "SBWindow.h"



enum class Input {
    NONE,
    PLAYER_MOVE_FORWARD,
    PLAYER_MOVE_BACKWARD,
    PLAYER_MOVE_LEFT,
    PLAYER_MOVE_RIGHT,

    COUNT
};

class InputManager {

public:

    using InputEvent = std::pair<Input, KeyAction>;

    explicit InputManager(const SBWindow& window);

    void fillCommandQueue(std::vector<CommandRef>& queue);

    void assignCommandToInputEvent(InputEvent event, CommandRef cmd);
    void assignCommandToKeyEvent(Keyboard::KeyEvent event, CommandRef cmd);

    void mapKeyToInput(Keyboard::Key key, Input input);

    SBWindow::CursorPos getCursorPos() const;
    bool isKeyDown(Keyboard::Key key) const;

private:
    const SBWindow& m_window;

    // Maps keys to input events.
    std::unordered_map<Keyboard::Key, Input> m_keyMapping;

    std::multimap<InputEvent, CommandRef> m_inputeventCommandMapping;
    std::multimap<Keyboard::KeyEvent, CommandRef> m_keyeventCommandMapping;

};

#endif //SPACEBOIS_INPUTMANAGER_H
