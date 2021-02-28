#ifndef CONTROLLED_OBJECT_H
#define CONTROLLED_OBJECT_H

#include "Sprite.hpp"

#include <iostream>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Tile.hpp"

using namespace std;

class ControlledObject : public Sprite {
    private:
        GLfloat speed;

    public:
        ControlledObject(char* textureSource, glm::vec2 position, int layer, GLfloat speed);

        void onStart();
        void onUpdate();

        string getClassId();
};

#endif