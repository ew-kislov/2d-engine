#ifndef CONTROLLED_OBJECT_H
#define CONTROLLED_OBJECT_H

#include "OpenglObject.cpp"

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
        ControlledObject(char* vertexShaderSource, char* fragmentShaderSource, char* textureSource, glm::vec3 position, int layer, GLfloat speed):
            OpenglObject(vertexShaderSource, fragmentShaderSource, textureSource, position, layer) {

            this->movement = glm::mat4(1.0);
            this->speed = speed;
        }

        void move(glm::vec3 movementVector, vector<vector<Tile*>> map) {
            movementVector = movementVector * speed;

            bool canMove = true;

            MathUtils::Rect* newRect = this->getBoundingRect();
            newRect->x0 += movementVector.x;
            newRect->x1 += movementVector.x;
            newRect->y0 += movementVector.y;
            newRect->y1 += movementVector.y;

            for (int i = 0; i < map.size(); i++) {
                for (int j = 0; j < map[i].size(); j++) {
                    if (!map[i][j]->isWalkable() && MathUtils::areRectsIntercepting(newRect, map[i][j]->getBoundingRect())) {
                        canMove = false;
                        break;
                    }
                }
            }

            if (canMove) {
                this->movement = glm::translate(this->movement, movementVector);
            }
        }

        virtual void transform(glm::mat4 projectionMatrix) {
            this->applyTransformationMatrix(projectionMatrix * this->movement * this->positionMatrix);
        }

        virtual MathUtils::Rect* getBoundingRect() {
            glm::vec4 d0 = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
            glm::vec4 d1 = glm::vec4(1.0f * width, 1.0f * height, 0.0f, 1.0f);

            glm::vec4 transformedD0 = this->movement * this->positionMatrix * d0;
            glm::vec4 transformedD1 = this->movement * this->positionMatrix * d1;

            return new MathUtils::Rect(transformedD0.x, transformedD0.y, transformedD1.x, transformedD1.y);
        }
};

#endif