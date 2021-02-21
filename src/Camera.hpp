#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
    private:
        glm::mat4 projectionMatrix;

    public:
        Camera() {};

        void setProjection(glm::mat4 projectionMatrix) {
            this->projectionMatrix = projectionMatrix;
        }

        glm::mat4 getProjection() {
            return this->projectionMatrix;
        }
};

#endif