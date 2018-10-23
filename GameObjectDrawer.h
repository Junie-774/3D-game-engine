//
// Created by kyle on 9/8/18.
//

#ifndef SPACEBOIS_GAMEOBJECTDRAWER_H
#define SPACEBOIS_GAMEOBJECTDRAWER_H

#include "GameObject.h"
#include "OpenGL/GLMeshDrawer.h"
#include "ShaderProgram.h"

class GameObjectDrawer {
public:
    void draw(const GameObject& obj, const GLMeshDrawer& meshDrawer, ShaderProgram& program) const;
};


#endif //SPACEBOIS_GAMEOBJECTDRAWER_H
