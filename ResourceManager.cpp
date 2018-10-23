//
// Created by kyle on 7/21/18.
//

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "ResourceManager.h"

std::unordered_map<std::string, std::mutex> ResourceManager::m_fileMutexes;

std::string ResourceManager::loadFileContents(std::string path) const {

    auto& fileMutex = m_fileMutexes[path];
    std::lock_guard fileLock(fileMutex);

    try {
        std::ifstream file(path);
        file.exceptions(std::ifstream::failbit);

        return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    }
    catch (std::ifstream::failure& fail) {
        std::cerr << "Error while opening file: " << path << "\n";
        return "";
    }
}

const GLTexture ResourceManager::addTexture(std::string name, std::string path, bool alpha) {

    std::pair<decltype(m_textures)::iterator, bool> result = m_textures.insert(
            std::pair(
                    std::move(name),
                    loadTextureFromFile(std::move(path))
                    )
                    );

    if (!result.second) {
        std::cerr << "Error when inserting texture into map\n";
    }

    return result.first->second;
}

const GLTexture ResourceManager::getTexture(std::string name) {

    return m_textures.at(name);
}

Model& ResourceManager::addModel(std::string name, std::string path) {
    auto result = m_models.insert({std::move(name), loadModelFromFile(std::move(path))});

    if (!result.second) {
        std::cerr << "Error when inserting model into map\n";
    }

    return result.first->second;
}

GLTexture ResourceManager::loadTextureFromFile(std::string path) {

    GLTexture::TextureOptions opts;
    int loadedChannel;
    unsigned char* image;

    {
        auto& fileMutex = m_fileMutexes[path];
        std::lock_guard fileLock(fileMutex);
        image = SOIL_load_image(path.c_str(), (int*) (&opts.dimensions.x), (int*) (&opts.dimensions.y), &loadedChannel, SOIL_LOAD_AUTO);
    }

    if (image == nullptr) {
        std::cerr << "Error while loading image from file: " << path << ", SOIL image load failed\n";
    }

    GLenum glFormat = (loadedChannel == SOIL_LOAD_RGBA) ? GL_RGBA : GL_RGB;

    GLTexture tex(opts, image, glFormat);
    SOIL_free_image_data(image);

    return tex;
}

Model ResourceManager::loadModelFromFile(std::string path) {

    std::lock_guard fileLock(m_fileMutexes[path]);
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_OptimizeMeshes);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error loading file! Assimp error message: " << importer.GetErrorString() << "\n";
    }

    std::vector<GLMesh> meshes;
    auto directory = path.substr(0, path.find_last_of('/'));
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        meshes.push_back(getMeshFromAssimp(scene->mMeshes[i], scene, directory));
    }


    return Model(std::move(meshes));
}

GLMesh ResourceManager::getMeshFromAssimp(const aiMesh* const mesh, const aiScene* const scene, const std::string& directory) {

    std::vector<GLVertex> vertices;
    std::vector<GLuint> indices;
    Material mat;

    // Assign vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        vertices.push_back(GLVertex {
                {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z},
                {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z},
                (mesh->mTextureCoords[0] ?
                     glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) :
                     glm::vec2(0.0f, 0.0f))
        });
    }

    // Assign indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex > 0) {
        aiMaterial* aiMat = scene->mMaterials[mesh->mMaterialIndex];
        mat = getMaterialFromAssimp(aiMat, directory);
    }

    return GLMesh(vertices, indices, mat);
}

Material ResourceManager::getMaterialFromAssimp(aiMaterial* mat, const std::string& directory) {
    Material ret;

    for (unsigned int i = 0, numMats = mat->GetTextureCount(aiTextureType_DIFFUSE); i < numMats; i++) {
        aiString texPath;
        mat->GetTexture(aiTextureType_DIFFUSE, i, &texPath);

        ret.diffuseMap.push_back(loadTextureFromFile(std::string(directory + "/" + texPath.C_Str())));
    }

    if (mat->GetTextureCount(aiTextureType_SPECULAR) > 0) {
        aiString texPath;
        mat->GetTexture(aiTextureType_SPECULAR, 0, &texPath);

        ret.specularMap.push_back(loadTextureFromFile(directory + "/" + texPath.C_Str()));
    }

    return ret;
}
