#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

#include "ControlledObject.hpp"

class Camera {
    private:
        glm::mat4 projectionMatrix;
        glm::mat4 lookAtMatrix;

    public:
        Camera();

        void setProjection(glm::mat4 projectionMatrix);
        void setTargetInitialPosition(ControlledObject* target);
        void moveTarget(glm::vec2 vector);
        glm::mat4 getProjection();
        glm::mat4 getTransformation();
};

#endif