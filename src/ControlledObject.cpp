#pragma once

#include "ControlledObject.hpp"

#include "Window.cpp"
#include "Camera.cpp"

ControlledObject::ControlledObject(char* textureSource, glm::vec2 position, int layer, GLfloat speed):
    Sprite(textureSource, position, layer) {
    this->speed = speed;
}

void ControlledObject::onStart() {
    // Do nothing
}

void ControlledObject::onUpdate() {
    glm::vec2 movementVector = glm::vec2(
        Window::isKeyPressed(EKey::A) ? -1.0 * this->speed : Window::isKeyPressed(EKey::D) ? 1.0 * this->speed : 0.0,
        Window::isKeyPressed(EKey::W) ? -1.0 * this->speed : Window::isKeyPressed(EKey::S) ? 1.0 * this->speed : 0.0
    );

    bool canMove = true;

    MathUtils::Rect* newRect = this->getBoundingRect();

    newRect->x0 += movementVector.x;
    newRect->x1 += movementVector.x;
    newRect->y0 += movementVector.y;
    newRect->y1 += movementVector.y;

    auto tiles = this->getScene()->getSprites("Tile");

    for (Sprite* baseTile: tiles) {
        Tile* tile = (Tile*)baseTile;
        if (!tile->isWalkable() && MathUtils::areRectsIntercepting(newRect, tile->getBoundingRect())) {
            canMove = false;
            break;
        }
    }

    if (canMove) {
        this->position += movementVector;
    }
}

string ControlledObject::getClassId() {
    return "ControlledObject";
}