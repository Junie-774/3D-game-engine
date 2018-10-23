//
// Created by kyle on 7/16/18.
//

#ifndef SPACEBOIS_SBWINDOW_H
#define SPACEBOIS_SBWINDOW_H

#include <functional>
#include <memory>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Keyboard.h"

namespace std {
    template <>
    struct default_delete<GLFWwindow> {
        void operator() (GLFWwindow* win) { glfwDestroyWindow(win); }
    };
}

class SBWindow {
public:
    using CursorPos = glm::vec2;

    struct WindowPos {
        int x;
        int y;
    };

    struct WindowSize {
        int width = 800;
        int height = 600;
    };

    explicit SBWindow(std::string title, WindowSize dims = {800, 600} );

    // Sets the OpenGL current context to this window
    void setActive();

    // Updates the image on the screen, polls for events,
    // does things that generally happen in a loop
    void update();

    bool shouldClose();

    CursorPos getCursorPos() const;

    const Keyboard& getKeyboard() const {return m_keyboard;}
private:

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    // Automatically handle deallocation of the window.
    std::unique_ptr<GLFWwindow> m_glfwWindow;

    std::string m_title;
    WindowSize m_dims;
    WindowPos m_pos;

    Keyboard m_keyboard;
};


#endif //SPACEBOIS_SBWINDOW_H
