#ifndef CONTROLLED_OBJECT_H
#define CONTROLLED_OBJECT_H

#include "OpenglObject.cpp"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;


class ControlledObject : public OpenglObject {
    private:
        glm::mat4 movement;

    public:
        ControlledObject(char* vertexShaderSource, char* fragmentShaderSource, char* textureSource, glm::vec3 position, int layer):
            OpenglObject(vertexShaderSource, fragmentShaderSource, textureSource, position, layer) {
            this->movement = glm::mat4(1.0);
        }

        void move(glm::vec3 movementVector) {
            this->movement = glm::translate(this->movement, movementVector);
        }

        virtual void transform(glm::mat4 projectionMatrix) {
            this->applyTransformationMatrix(projectionMatrix * this->movement * this->positionMatrix);
        }
};

#endif