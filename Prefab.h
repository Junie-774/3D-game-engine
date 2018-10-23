//
// Created by kyle on 9/8/18.
//

#ifndef SPACEBOIS_PREFAB_H
#define SPACEBOIS_PREFAB_H

#include <memory>
#include "GameObject.h"

template <typename... Components>
class Prefab {
public:
    GameObject generate(GameObjectID id) {

        GameObject obj(std::move(id));
        addComponents(obj);
        return obj;
    };
private:

    void addComponents(GameObject& obj) {

        if constexpr (sizeof...(Components) > 0) {
            obj.addComponents(Components(obj)...);
        }
    }

};


#endif //SPACEBOIS_PREFAB_H
