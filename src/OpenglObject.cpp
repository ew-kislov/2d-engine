#pragma once

#include "OpenglObject.hpp"

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

OpenglObject::OpenglObject(char* vertexShaderSource, char* fragmentShaderSource, char* textureSource, glm::vec3 position) {
    this->vertexShaderSource = vertexShaderSource;
    this->fragmentShaderSource = fragmentShaderSource;
    this->textureSource = textureSource;
    this->positionMatrix = glm::translate(position);

    this->programId = OpenglUtils::createShaderProgram(this->vertexShaderSource, this->fragmentShaderSource);

    glUseProgram(this->programId);

    this->setPreview();
}

void OpenglObject::setPreview() {
    GLuint positionVbo;
    GLuint textureCoordVbo;
    GLuint textureId;

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    int width, height, channels;
    unsigned char *textureData = stbi_load(this->textureSource, &width, &height, &channels, 0);

    /**
     * initiate vertex data
     */

    GLfloat* positionData = new GLfloat[12] {
        0.0f, 0.0f,
        0.0f, 1.0f * height,
        1.0f * width, 0.0f,

        0.0f, 1.0f * height,
        1.0f * width, 0.0f,
        1.0f * width, 1.0f * height
    };

    glGenBuffers(1, &positionVbo);
    glBindBuffer(GL_ARRAY_BUFFER, positionVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, positionData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    this->vbos[VboType::Position] = positionVbo;

    /**
     * initiate texture coord data
     */

    // GLfloat* textureСoordData = new GLfloat[12] {
    //     0.0f, 0.0f,
    //     0.0f, 1.0f,
    //     1.0f, 0.0f,

    //     0.0f, 1.0f,
    //     1.0f, 0.0f,
    //     1.0f, 1.0f
    // };

    cout << "Fucking shit" << endl;
    cout << glm::to_string(MathUtils::projectionMatrix * this->positionMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) << endl;
    cout << glm::to_string(MathUtils::projectionMatrix * this->positionMatrix * glm::vec4(0.0f, 1.0f * height, 0.0f, 1.0f)) << endl;
    cout << glm::to_string(MathUtils::projectionMatrix * this->positionMatrix * glm::vec4(1.0f * width, 0.0f, 0.0f, 1.0f)) << endl;
    cout << glm::to_string(MathUtils::projectionMatrix * this->positionMatrix * glm::vec4(1.0f * width, 1.0f * height, 0.0f, 1.0f)) << endl;

    // glGenBuffers(1, &textureCoordVbo);
    // glBindBuffer(GL_ARRAY_BUFFER, textureCoordVbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, textureСoordData, GL_STATIC_DRAW);

    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    // this->vbos[VboType::TextureCoords] = textureCoordVbo;

    /**
     * load texture
     */

    // glGenTextures(1, &this->textureId);
    // glBindTexture(GL_TEXTURE_2D, this->textureId);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // if (textureData) {
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    //     glGenerateMipmap(GL_TEXTURE_2D);
    // }
    // else {
    //     cout << "Failed to load texture" << endl;
    // }

    // stbi_image_free(textureData);
}

void OpenglObject::applyTransformationMatrix(glm::mat4 matrix) {
    glUseProgram(this->programId);
    OpenglUtils::setUniformMat4(this->programId, "transform_matrix", matrix * this->positionMatrix);
}

void OpenglObject::draw() {
    // glBindTexture(GL_TEXTURE_2D, this->textureId);
    glUseProgram(this->programId);
    glBindVertexArray(this->vao);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}