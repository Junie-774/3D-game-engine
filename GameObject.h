//
// Created by kyle on 8/11/18.
//

#ifndef SPACEBOIS_GAMEOBJECT_H
#define SPACEBOIS_GAMEOBJECT_H

#include <memory>
#include <optional>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include "Component/Component.h"
#include "Model.h"
#include "Scripts/Script.h"
#include "Transform.h"


using GameObjectID = std::string;
/**
 * @brief Represent objects within the game. GameObjects are differentiated by their components, scripts, and model.
 */
class GameObject {
public:
    using reference = std::reference_wrapper<GameObject>;

    explicit GameObject(GameObjectID id) noexcept;

    GameObjectID id() const;
    /**
     * @brief Updates Scripts and other components which need to be updated
     */
    virtual void update();

    /**
     * @brief All GameObjects have a Transform. Retrieves the GameObject's m_transform field
     * @return A reference to the GameObject's m_transform field
     */
    Transform& getTransform();

    const Transform& getTransform() const;

    /**
     * @brief Adds a component to the GameObject
     * @param newScript
     */
     template <typename S>
    void addScript(S newScript) {

        std::unique_ptr<S> toAdd = std::make_unique<S>(std::move(newScript));
        std::unique_ptr<Script> basePtr(dynamic_cast<Script*>(toAdd.release()));

        m_scripts.push_back(std::move(basePtr));
        m_scripts.rbegin()->get()->start();
    }

    /**
     * @brief Adds a component to the gameobject
     * @param newComponent the component to add
     */
    template<typename Comp>
    std::optional<ComponentRef> addComponent(Comp newComponent) {
        static_assert(std::is_base_of<Component, Comp>::value, "Error in addComponent(): Given type is not a component.");
        static_assert(has_type_string<Comp>::value,
                      "Error in addComponent(): given type doesn't have const static member string named TYPE");

        std::unique_ptr<Comp> toAdd = std::make_unique<Comp>(std::move(newComponent));
        std::unique_ptr<Component> basePtr(dynamic_cast<Component*>(toAdd.release()));

        auto result = m_components.emplace(basePtr->type(), std::move(basePtr));

        if (!result.second) {
            std::cerr << "Error in addComponent(): argument already exists\n";
            return std::nullopt;
        }

        return *result.first->second;
    }

    /**
     * @brief Adds a variable number of components to the gameobject
     * @tparam Comp
     * @tparam Comps
     * @param comp
     * @param rest
     */
    template<class Comp, class... Comps>
    void addComponents(Comp first, Comps... rest) {

        // Allocate a new Derived
        addComponent(first);

        if constexpr (sizeof...(Comps) != 0) {
            addComponents(rest...);
        }
    }

    /**
     * @brief If the given template parameter has a static TYPE field and derives from Component,
     * checks if the GameObject has such a component, and returns it if so
     * @tparam T Type of component to find
     * @return The found component, if T has a std::string type() member function and exists in this GameObject
     *         OR
     *         std::nullopt, if T does not meet the type requirements or if no such object exists
     */
    // Holy wow SFINAE is really cool
    template <typename T>
    std::optional<std::reference_wrapper<T>> getComponent() {

        static_assert(std::is_base_of<Component, T>::value, "Error in getComponent(): type given is not a component");
        static_assert(has_type_string<T>::value,
                      "Error in getComponent(): given type doesn't have const static member string named TYPE");

        auto itr = m_components.find(T::TYPE);

        if (itr == m_components.end()) {
            return std::nullopt;
        }

        return dynamic_cast<T&>(*itr->second);
    }



    /**
     * @brief Template specialization of GameObject::getComponent() for invalid types
     * @tparam T A type which does not contain the type information needed to use getComponent(), and so has fallen through
     * to this overload
     * @return std::nullopt
     */
    template<typename T>
    typename std::enable_if<!has_type_string<T>::value,
            std::optional<std::reference_wrapper<T>>>::type
    getComponent() {
        return std::nullopt;
    }

    /**
     * @brief Attempts to retrGLX_nvidiaieve a component given a string representing it's type. Cumbersome to use because
     * the returned component needs to be casted
     * @param componentType A string denoting the type of component
     * @return A polymorphic reference to the found component which must be casted to the correct type
     *         OR
     *         std::nullopt if the component wasn't found
     */
    std::optional<ComponentRef> getComponent(std::string componentType);

    void setModel(Model model);

    const std::optional<Model>& model() const;

    std::optional<Model>& model();

private:
    GameObjectID m_id;

    Transform m_transform;

    std::unordered_map<std::string, std::unique_ptr<Component>> m_components;

    std::vector<std::unique_ptr<Script>> m_scripts;

    std::optional<Model> m_model;

};

typedef std::reference_wrapper<GameObject> GameObjectRef;


#endif //SPACEBOIS_GAMEOBJECT_H
