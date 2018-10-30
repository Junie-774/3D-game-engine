//
// Created by kyle on 7/16/18
//

#include "SBWindow.h"
#include "InputManager.h"


SBWindow::SBWindow(std::string title, SBWindow::WindowSize dims)
        : m_title(std::move(title)),
          m_dims(dims),
          m_pos{0, 0},
          m_glfwWindow(nullptr),
          m_keyboard{}
{
    glfwInit();

    // Window information for glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    m_glfwWindow.reset(glfwCreateWindow(m_dims.width, m_dims.height, m_title.c_str(), nullptr, nullptr));
    glfwSetWindowUserPointer(m_glfwWindow.get(), this);
    glfwSetKeyCallback(m_glfwWindow.get(), keyCallback);

    glfwSetInputMode(m_glfwWindow.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void SBWindow::setActive() {

    glfwMakeContextCurrent(m_glfwWindow.get());
}

void SBWindow::update() {

    glfwSwapBuffers(m_glfwWindow.get());
    glfwPollEvents();
}

bool SBWindow::shouldClose() {

    return static_cast<bool>(glfwWindowShouldClose(m_glfwWindow.get()));
}

SBWindow::CursorPos SBWindow::getCursorPos() const {

    double x, y;
    glfwGetCursorPos(m_glfwWindow.get(), &x, &y);

    return glm::vec2(x, m_dims.height - y);
}

void SBWindow::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto SBwindow = static_cast<SBWindow*>(glfwGetWindowUserPointer(window));
    SBwindow->m_keyboard.keyCallback(key, action);
}