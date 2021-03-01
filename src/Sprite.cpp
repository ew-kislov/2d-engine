#pragma once

#include "Sprite.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "OpenglUtils.cpp"
#include "MathUtils.cpp"

#include "BaseObject.cpp"
#include "Camera.cpp"

Sprite::Sprite(char* textureSource, glm::vec2 position, int layer):
    BaseObject("src/fragment_shader.glsl", "src/vertex_shader.glsl", position, layer) {
    this->textureSource = textureSource;
}

void Sprite::init() {
    this->position = this->initialPosition;

    GLuint positionVbo;
    GLuint textureCoordVbo;
    GLuint textureId;

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    int channels;
    unsigned char *textureData = stbi_load(this->textureSource, &this->width, &this->height, &channels, 0);

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

    GLfloat* textureСoordData = new GLfloat[12] {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f
    };

    glGenBuffers(1, &textureCoordVbo);
    glBindBuffer(GL_ARRAY_BUFFER, textureCoordVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, textureСoordData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    this->vbos[VboType::TextureCoords] = textureCoordVbo;

    /**
     * load texture
     */

    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, channels == 4 ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, channels == 4 ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (textureData) {
        glTexImage2D(GL_TEXTURE_2D, 0, channels == 3 ? GL_RGB : GL_RGBA, width, height, 0, channels == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        cout << "Failed to load texture" << endl;
    }

    stbi_image_free(textureData);
}

void Sprite::draw() {
    glUseProgram(this->programId);

    glm::mat4 cameraMatrix = Camera::getResultMatrix();
    OpenglUtils::setUniformMat4(
        this->programId,
        "transform_matrix",
        cameraMatrix * glm::translate(glm::vec3(this->position, 0.0f))
    );

    glBindTexture(GL_TEXTURE_2D, this->textureId);
    glBindVertexArray(this->vao);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

MathUtils::Rect* Sprite::getBoundingRect() {
    glm::vec4 d0 = glm::vec4(1.0f * this->position.x, 1.0f * this->position.y, 0.0f, 1.0f);
    glm::vec4 d1 = glm::vec4(1.0f * (width + this->position.x), 1.0f * (height + this->position.y), 0.0f, 1.0f);

    return new MathUtils::Rect(d0.x, d0.y, d1.x, d1.y);
}