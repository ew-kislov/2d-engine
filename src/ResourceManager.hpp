#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>

#include <glm/glm.hpp>

#include "Texture.hpp"
#include "Font.hpp"

using namespace std;


class ResourceManager {
    private:
        static map<string, Texture*> textures;
        static map<string, Font*> fonts;

        static string getFontHash(string source, int size);

    public:
        static void loadTexture(string textureSource);
        static void loadFont(string fontSource, int size);

        static Texture* getTexture(string textureSource);
        static Font* getFont(string fontSource, int size);
};

#endif