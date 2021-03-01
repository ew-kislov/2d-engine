#ifndef WINNING_DOOR_H
#define WINNING_DOOR_H

#include "Sprite.hpp"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;

class WinningDoor : public Sprite {
    public:
        WinningDoor(char* textureSource, glm::vec2 position, int layer);

        void onStart();
        void onUpdate();

        string getClassId();
};

#endif