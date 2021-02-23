#ifndef CONTROLLED_OBJECT_H
#define CONTROLLED_OBJECT_H

#include "OpenglObject.hpp"

#include <iostream>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Tile.hpp"

using namespace std;

class ControlledObject : public OpenglObject {
    private:
        glm::mat4 movement;
        GLfloat speed;

    public:
        ControlledObject(char* vertexShaderSource, char* fragmentShaderSource, char* textureSource, glm::vec3 position, int layer, GLfloat speed);

        void move(glm::vec3 movementVector);
        virtual void transform();
        virtual MathUtils::Rect* getBoundingRect();
};

#endif