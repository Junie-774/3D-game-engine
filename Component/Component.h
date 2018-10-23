//
// Created by kyle on 8/22/18.
//

#ifndef SPACEBOIS_COMPONENT_H
#define SPACEBOIS_COMPONENT_H

#include <vector>
#include <memory>
#include <utility>

class GameObject;

class Component {
public:

    virtual const std::string type() const = 0;
    explicit Component(GameObject& parent);

protected:
    GameObject& m_gameObj;
};

template <typename T>
class ComponentTraits {
    static const std::string type() { return T::TYPE; }
};

template <class T>
class has_type_string {

    template <typename U, typename = typename std::enable_if<!std::is_member_pointer<decltype(&U::TYPE)>::value>::type>
    static constexpr bool test(int) {
        return true;
    }

    template <typename>
    static constexpr bool test(...) {
        return false;
    }


public:
    const static bool value = test<T>(int());
};

typedef std::reference_wrapper<Component> ComponentRef;


#endif //SPACEBOIS_COMPONENT_H
