#pragma once

#include "Sprite.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#include "OpenglUtils.cpp"
#include "MathUtils.cpp"

#include "BaseObject.cpp"
#include "Camera.cpp"
#include "Texture.cpp"

#include "OpenGL.cpp"

Sprite::Sprite(Texture* texture, glm::vec2 position, int layer):
    BaseObject("src/fragment_shader.glsl", "src/vertex_shader.glsl", position, layer) {
    this->texture = texture;
    this->height = texture->getHeight();
    this->width = texture->getWidth();
}

void Sprite::init() {
    this->position = this->initialPosition;

    GLuint positionVbo;
    GLuint textureCoordVbo;

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    /**
     * initiate vertex data
     */

    GLfloat z = 1.0 * this->layer / MAX_LAYERS + MIN_Z;

    GLfloat* positionData = new GLfloat[18] {
        0.0f, 0.0f, z,
        0.0f, 1.0f * this->height, z,
        1.0f * this->width, 0.0f, z,

        0.0f, 1.0f * this->height, z,
        1.0f * this->width, 0.0f, z,
        1.0f * this->width, 1.0f * this->height, z
    };

    glGenBuffers(1, &positionVbo);
    glBindBuffer(GL_ARRAY_BUFFER, positionVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18, positionData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    this->vbos[VboType::Position] = positionVbo;

    /**
     * initiate texture coord data
     */

    GLfloat* textureCoords = new GLfloat[12] {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    glGenBuffers(1, &textureCoordVbo);
    glBindBuffer(GL_ARRAY_BUFFER, textureCoordVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, textureCoords, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    this->vbos[VboType::TextureCoords] = textureCoordVbo;
}

void Sprite::draw() {
    if (this->isOutOfWindow()) {
        return;
    }

    OpenGL::useProgram(this->programId);

    glm::mat4 cameraMatrix = Camera::getResultMatrix();
    OpenglUtils::setUniformMat4(
        this->programId,
        "transform_matrix",
        cameraMatrix * glm::translate(glm::vec3(this->position, 0.0f))
    );

    OpenGL::bindTexture(this->texture->getId());
    OpenGL::bindVao(this->vao);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

MathUtils::Rect* Sprite::getBoundingRect() {
    glm::vec4 d0 = glm::vec4(1.0f * this->position.x, 1.0f * this->position.y, 0.0f, 1.0f);
    glm::vec4 d1 = glm::vec4(1.0f * (width + this->position.x), 1.0f * (height + this->position.y), 0.0f, 1.0f);

    return new MathUtils::Rect(d0.x, d0.y, d1.x, d1.y);
}

bool Sprite::isOutOfWindow() {
    MathUtils::Rect* rect = this->getBoundingRect();
    glm::vec2 cameraPosition = Camera::getPosition();

    return rect->y1 + cameraPosition.y < 0 || rect->x1 + cameraPosition.x < 0 || rect->y0 + cameraPosition.y > Window::getHeight() || rect->x0 + cameraPosition.x > Window::getWidth();
}