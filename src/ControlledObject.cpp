#pragma once

#include "ControlledObject.hpp"

#include "Window.cpp"

#include "Camera.cpp"

ControlledObject::ControlledObject(char* textureSource, glm::vec3 position, int layer, GLfloat speed):
    OpenglObject(textureSource, position, layer) {

    this->movement = glm::mat4(1.0);
    this->speed = speed;
}

void ControlledObject::move() {
    glm::vec2 movementVector = glm::vec2(
        Window::isKeyPressed(EKey::A) ? -1.0 : Window::isKeyPressed(EKey::D) ? 1.0 : 0.0,
        Window::isKeyPressed(EKey::W) ? -1.0 : Window::isKeyPressed(EKey::S) ? 1.0 : 0.0
    );

    movementVector = movementVector * speed;

    bool canMove = true;

    MathUtils::Rect* newRect = this->getBoundingRect();
    newRect->x0 += movementVector.x;
    newRect->x1 += movementVector.x;
    newRect->y0 += movementVector.y;
    newRect->y1 += movementVector.y;

    auto tiles = this->getScene()->getSprites("Tile");

    for (OpenglObject* baseTile: tiles) {
        Tile* tile = (Tile*)baseTile;
        if (!tile->isWalkable() && MathUtils::areRectsIntercepting(newRect, tile->getBoundingRect())) {
            canMove = false;
            break;
        }
    }

    if (canMove) {
        this->movementVector += movementVector;
        this->movement = glm::translate(this->movement, glm::vec3(movementVector, 0.0f));
    }
}

void ControlledObject::transform() {
    glm::mat4 cameraMatrix = Camera::getResultMatrix();
    this->applyTransformationMatrix(cameraMatrix * this->movement * this->positionMatrix);
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