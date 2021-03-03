#pragma once

#include "ControlledObject.hpp"

#include "Window.cpp"
#include "Camera.cpp"

ControlledObject::ControlledObject(Texture* texture, glm::vec2 position, int layer, GLfloat speed):
    Sprite(texture, position, layer) {
    this->speed = speed;
}

void ControlledObject::onStart() {
    // Do nothing
}

void ControlledObject::onUpdate(double deltaTime) {
    glm::vec2 xMovementVector = glm::vec2(
        Window::isKeyPressed(EKey::A) ? -1.0 * deltaTime / 20 * this->speed : Window::isKeyPressed(EKey::D) ? 1.0 * deltaTime / 20 * this->speed : 0.0,
        0.0
    );

    glm::vec2 yMovementVector = glm::vec2(
        0.0,
        Window::isKeyPressed(EKey::W) ? -1.0 * deltaTime / 20 * this->speed : Window::isKeyPressed(EKey::S) ? 1.0 * deltaTime / 20 * this->speed : 0.0
    );

    bool canMoveX = true;
    bool canMoveY = true;

    MathUtils::Rect* newRectX = this->getBoundingRect();
    MathUtils::Rect* newRectY = this->getBoundingRect();

    newRectX->x0 += xMovementVector.x;
    newRectX->x1 += xMovementVector.x;
    newRectY->y0 += yMovementVector.y;
    newRectY->y1 += yMovementVector.y;

    auto tiles = this->getScene()->getSprites("Tile");

    for (Sprite* baseTile: tiles) {
        Tile* tile = (Tile*)baseTile;
        if (!tile->isWalkable() && MathUtils::areRectsIntercepting(newRectX, tile->getBoundingRect())) {
            canMoveX = false;
        }
        if (!tile->isWalkable() && MathUtils::areRectsIntercepting(newRectY, tile->getBoundingRect())) {
            canMoveY = false;
        }
        if (!canMoveX && !canMoveY) {
            break;
        }
    }

    if (canMoveX) {
        this->position += xMovementVector;
    }
    if (canMoveY) {
        this->position += yMovementVector;
    }
}

string ControlledObject::getClassId() {
    return "ControlledObject";
}