#pragma once

#include "WinningDoor.hpp"

#include "Sprite.cpp"
#include "Game.cpp"

WinningDoor::WinningDoor(char* textureSource, glm::vec2 position, int layer):
    Sprite(textureSource, position, layer) {
}

void WinningDoor::onStart() {
    // Do nothing
}

void WinningDoor::onUpdate() {
    Sprite* mainCharacter = this->getScene()->find("Main character");
    if (MathUtils::areRectsIntercepting(this->getBoundingRect(), mainCharacter->getBoundingRect())) {
        Game::setActiveScene("Win");
    }
}

string WinningDoor::getClassId() {
    return "WinningDoor";
}