#pragma once

#include "ControlledObject.hpp";

#include "Window.cpp"

ControlledObject::ControlledObject(char* vertexShaderSource, char* fragmentShaderSource, char* textureSource, glm::vec3 position, int layer, GLfloat speed):
     OpenglObject(vertexShaderSource, fragmentShaderSource, textureSource, position, layer) {

    this->movement = glm::mat4(1.0);
    this->speed = speed;

    ObjectPool* objectPool = ObjectPool::getInstance();
    if (objectPool->getControlledObject() != nullptr) {
        throw runtime_error("Controlled object was already initialized");
    }
    objectPool->setControlledObject(this);
}

void ControlledObject::move() {
    glm::vec3 movementVector = glm::vec3(
        Window::isKeyPressed(EKey::A) ? -1.0 : Window::isKeyPressed(EKey::D) ? 1.0 : 0.0,
        Window::isKeyPressed(EKey::W) ? -1.0 : Window::isKeyPressed(EKey::S) ? 1.0 : 0.0,
        0.0
    );

    movementVector = movementVector * speed;

    bool canMove = true;

    MathUtils::Rect* newRect = this->getBoundingRect();
    newRect->x0 += movementVector.x;
    newRect->x1 += movementVector.x;
    newRect->y0 += movementVector.y;
    newRect->y1 += movementVector.y;

    vector<Tile*> map = ObjectPool::getInstance()->getMap();

    for (int i = 0; i < map.size(); i++) {
        if (!map[i]->isWalkable() && MathUtils::areRectsIntercepting(newRect, map[i]->getBoundingRect())) {
            canMove = false;
            break;
        }
    }

    if (canMove) {
        this->movement = glm::translate(this->movement, movementVector);
        ObjectPool::getInstance()->getCamera()->moveTarget(glm::vec2(movementVector.x, movementVector.y));
    }
}

void ControlledObject::transform() {
    glm::mat4 projectionMatrix = ObjectPool::getInstance()->getCamera()->getTransformation();
    this->applyTransformationMatrix(projectionMatrix * this->movement * this->positionMatrix);
}

MathUtils::Rect* ControlledObject::getBoundingRect() {
    glm::vec4 d0 = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 d1 = glm::vec4(1.0f * width, 1.0f * height, 0.0f, 1.0f);

    glm::vec4 transformedD0 = this->movement * this->positionMatrix * d0;
    glm::vec4 transformedD1 = this->movement * this->positionMatrix * d1;

    return new MathUtils::Rect(transformedD0.x, transformedD0.y, transformedD1.x, transformedD1.y);
}

string ControlledObject::getClassId() {
    return "ControlledObject";
}