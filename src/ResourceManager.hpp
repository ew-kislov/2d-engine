#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>

#include <glm/glm.hpp>

#include "Texture.hpp"
#include "Font.hpp"

using namespace std;


class ResourceManager {
    private:
        static map<string, shared_ptr<Texture> > textures;
        static map<string, shared_ptr<Font> > fonts;

        static string getFontHash(string source, int size);

    public:
        static void loadTexture(string textureSource);
        static void loadFont(string fontSource, int size);

        static shared_ptr<Texture> getTexture(string textureSource);
        static shared_ptr<Font> getFont(string fontSource, int size);
};

#endif