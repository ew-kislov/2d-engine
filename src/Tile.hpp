#ifndef TILE_H
#define TILE_H

#include "OpenglObject.cpp"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;

class Tile : public OpenglObject {
    private:
        bool walkable;

    public:
        Tile(char* vertexShaderSource, char* fragmentShaderSource, char* textureSource, glm::vec3 position, int layer, bool walkable):
            OpenglObject(vertexShaderSource, fragmentShaderSource, textureSource, position, layer) {
            
            this->walkable = walkable;
        }

        virtual void transform(glm::mat4 projectionMatrix) {
            this->applyTransformationMatrix(projectionMatrix * this->positionMatrix);
        }

        virtual MathUtils::Rect* getBoundingRect() {
            glm::vec4 d0 = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
            glm::vec4 d1 = glm::vec4(1.0f * width, 1.0f * height, 0.0f, 1.0f);

            glm::vec4 transformedD0 = this->positionMatrix * d0;
            glm::vec4 transformedD1 = this->positionMatrix * d1;

            return new MathUtils::Rect(transformedD0.x, transformedD0.y, transformedD1.x, transformedD1.y);
        }

        bool isWalkable() {
            return this->walkable;
        }
};

#endif