#pragma once

#include "ResourceManager.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

#include "Texture.cpp"

map<char*, Texture*> ResourceManager::textures {};

void ResourceManager::loadTexture(char* textureSource) {
    int width, height, channels;
    GLuint textureId;

    unsigned char *textureData = stbi_load(textureSource, &width, &height, &channels, 0);

    if (!textureData) {
        throw runtime_error("Error: failed to load texture");
    }

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, channels == 4 ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, channels == 4 ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, channels == 3 ? GL_RGB : GL_RGBA, width, height, 0, channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureData);

    ResourceManager::textures[textureSource] = new Texture(textureId, width, height);
}

Texture* ResourceManager::getTexture(char* textureSource) {
    Texture* texture = ResourceManager::textures[textureSource];
    if (!texture) {
        throw runtime_error("Error: no texture with given source");
    }
    return texture;
}