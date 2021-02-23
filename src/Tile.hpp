#ifndef TILE_H
#define TILE_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;

class Tile : public OpenglObject {
    private:
        bool walkable;

    public:
        Tile(char* vertexShaderSource, char* fragmentShaderSource, char* textureSource, glm::vec3 position, int layer, bool walkable);

        virtual void transform();
        virtual MathUtils::Rect* getBoundingRect();
        bool isWalkable();
};

#endif