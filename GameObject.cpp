//
// Created by kyle on 8/11/18.
//

#include "GameObject.h"

GameObject::GameObject(GameObjectID id) noexcept
        : m_id(std::move(id))
{}

GameObjectID GameObject::id() const {
    return m_id;
}

Transform& GameObject::getTransform() {
    return m_transform;
}

const Transform& GameObject::getTransform() const {
    return m_transform;
}

void GameObject::update() {
    for (auto& script : m_scripts) {
        script->update();
    }
}


std::optional<ComponentRef> GameObject::getComponent(std::string componentType) {
    auto itr = m_components.find(componentType);

    if (itr == m_components.end()) {
        return std::nullopt;
    }

    return *itr->second;
}

void GameObject::setModel(Model model) {
    m_model = std::move(model);
}

const std::optional<Model>& GameObject::model() const {
    return m_model;
}

std::optional<Model>& GameObject::model() {
    return m_model;
}