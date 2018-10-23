//
// Created by kyle on 7/21/18.
//

#ifndef SPACEBOIS_RESOURCEMANAGER_H
#define SPACEBOIS_RESOURCEMANAGER_H

#include <fstream>
#include <iostream>
#include <mutex>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <assimp/scene.h>
#include <SOIL/SOIL.h>
#include "OpenGL/GLMesh.h"
#include "Model.h"
#include "OpenGL/GLTexture.h"

class ResourceManager {
public:
    std::string loadFileContents(std::string path) const;
    const GLTexture addTexture(std::string name, std::string path, bool alpha);
    const GLTexture getTexture(std::string name);

    Model& addModel(std::string name, std::string path);
    Model& getModel(std::string name);

public:
    static GLTexture loadTextureFromFile(std::string path);
    static Model loadModelFromFile(std::string path);

    std::unordered_map<std::string, GLTexture> m_textures;
    std::unordered_map<std::string, Model> m_models;

    // Lock individual files by their path
    static std::unordered_map<std::string, std::mutex> m_fileMutexes;

    static GLMesh getMeshFromAssimp(const aiMesh* mesh, const aiScene* scene, const std::string& directory);
    static Material getMaterialFromAssimp(aiMaterial* mat, const std::string& directory);
};


#endif //SPACEBOIS_RESOURCEMANAGER_H
