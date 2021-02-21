#ifndef TILE_H
#define TILE_H

#include "OpenglObject.cpp"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;

class Tile : public OpenglObject {
    public:
        Tile(char* vertexShaderSource, char* fragmentShaderSource, char* textureSource, glm::vec3 position):
            OpenglObject(vertexShaderSource, fragmentShaderSource, textureSource, position) {
        }
        virtual void transform(glm::mat4 projectionMatrix) {
            this->applyTransformationMatrix(projectionMatrix * this->positionMatrix);
        }
};

#endif