#pragma once

#include "Tile.hpp"

#include "Camera.cpp"

Tile::Tile(char* textureSource, glm::vec3 position, int layer, bool walkable):
    OpenglObject(textureSource, position, layer) {

    this->walkable = walkable;
}

void Tile::transform() {
    glm::mat4 cameraMatrix = Camera::getResultMatrix();
    this->applyTransformationMatrix(cameraMatrix * this->positionMatrix);
}

MathUtils::Rect* Tile::getBoundingRect() {
    glm::vec4 d0 = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 d1 = glm::vec4(1.0f * width, 1.0f * height, 0.0f, 1.0f);

    glm::vec4 transformedD0 = this->positionMatrix * d0;
    glm::vec4 transformedD1 = this->positionMatrix * d1;

    return new MathUtils::Rect(transformedD0.x, transformedD0.y, transformedD1.x, transformedD1.y);
}

bool Tile::isWalkable() {
    return this->walkable;
}

string Tile::getClassId() {
    return "Tile";
}

void Tile::move() {
}