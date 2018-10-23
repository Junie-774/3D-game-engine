//
// Created by kyle on 9/2/18.
//

#ifndef SPACEBOIS_KEYTRACKER_H
#define SPACEBOIS_KEYTRACKER_H

#include <array>
#include <unordered_set>
#include <utility>
#include <vector>
#include <GLFW/glfw3.h>


enum class KeyState {
    UP,
    DOWN
};

enum class KeyAction {
    PRESS,
    HOLD,
    RELEASE
};

class Keyboard {

    static constexpr unsigned int NUM_KEYS = GLFW_KEY_LAST;

public:

    using Key = decltype(GLFW_KEY_LAST);
    using KeyEvent = std::pair<Key, KeyAction>;

    void fillEventQueue(std::vector<KeyEvent>& toFill) const;
    bool isKeyDown(Key key) const;

private:
    friend class SBWindow;

    void keyDown(Key k);
    void keyUp(Key k);
    void keyCallback(Key k, int action);

    mutable std::vector<KeyEvent> m_newEvents;

    // Stores the state of each key
    std::array<KeyState, NUM_KEYS> m_keyStates;

    // To prevent having to iterate over all keys, we keep a shorter list of keys which are
    // currently held down
    std::unordered_set<Key> m_pressedKeys;
};


#endif //SPACEBOIS_KEYTRACKER_H
