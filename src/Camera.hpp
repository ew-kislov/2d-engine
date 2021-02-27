#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include "OpenglObject.hpp"

#include "Game.hpp"

class Camera {
    private:
        static int width;
        static int height;

        static glm::mat4 projectionMatrix;
        static glm::mat4 lookAtMatrix;

        static OpenglObject* target;

        friend class Game;

    public:
    static void move();
        static void setResolution(int width, int height);
        static void lookAt(OpenglObject* target);
        static glm::mat4 getResultMatrix();
        static glm::mat4 getProjectionMatrix();
};

#endif