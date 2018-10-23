//
// Created by kyle on 8/25/18.
//

#ifndef SPACEBOIS_MATERIAL_H
#define SPACEBOIS_MATERIAL_H

#include <optional>
#include <vector>
#include "OpenGL/GLTexture.h"

struct Material {
    std::vector<GLTexture> diffuseMap = {};
    std::vector<GLTexture> specularMap = {};
};



#endif //SPACEBOIS_MATERIAL_H
