#pragma once

#include "Tile.hpp"

#include "Camera.cpp"

Tile::Tile(char* textureSource, glm::vec2 position, int layer, bool walkable):
    Sprite(textureSource, position, layer) {
    this->walkable = walkable;
}

void Tile::onStart() {
    // Do nothing
}

void Tile::onUpdate() {
    // Do nothing
}

bool Tile::isWalkable() {
    return this->walkable;
}

string Tile::getClassId() {
    return "Tile";
}