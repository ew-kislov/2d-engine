#pragma once

#include "Label.hpp"

#include "TextLib.cpp"
#include "Camera.cpp"

Label::Label(string text, string fontSource, int size, glm::vec4 color, glm::vec3 position, int layer):
    BaseObject("src/label_fragment_shader.glsl", "src/label_vertex_shader.glsl", position, layer) {
    this->text = text;
    this->fontSource = fontSource;
    this->size = size;
    this->color = color;

    this->setPreview();
}

void Label::transform() {
    glm::mat4 cameraMatrix = Camera::getProjectionMatrix();
    this->applyTransformationMatrix(cameraMatrix * this->positionMatrix);
}

void Label::setPreview() {
    TextLib::initFont(fontSource, this->size);

    GLuint vbo;

    glUseProgram(programId);

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &vbo);
    this->vbos[VboType::Position] = vbo;

    glBindBuffer(GL_ARRAY_BUFFER, this->vbos[VboType::Position]);

    glUniform3f(glGetUniformLocation(programId, "textColor"), color.x, color.y, color.z);

    float x = this->position.x;
    float y = this->position.y;
    
    GLfloat* buffer = new GLfloat[text.size() * 24];

    for (int i = 0; i < text.size(); i++) {
        Character* ch = TextLib::getChar(text[i]);

        float xpos = x;
        float ypos = y + this->size - ch->bearing.y;

        float w = ch->size.x;
        float h = ch->size.y;

        GLfloat* vertices = new GLfloat[24] {
             xpos,     ypos + h,   0.0f, 1.0f ,            
             xpos,     ypos,       0.0f, 0.0f ,
             xpos + w, ypos,       1.0f, 0.0f ,

             xpos,     ypos + h,   0.0f, 1.0f ,
             xpos + w, ypos,       1.0f, 0.0f ,
             xpos + w, ypos + h,   1.0f, 1.0f       
        };

        memcpy(buffer + i * 24, vertices, 24 * sizeof(GLfloat));

        delete[] vertices;

        x += (ch->advance >> 6);
    }

    glBindBuffer(GL_ARRAY_BUFFER, this->vbos[VboType::Position]);
    glBufferData(GL_ARRAY_BUFFER, 24 * text.size() * sizeof(GLfloat), buffer, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    delete[] buffer;
}

void Label::draw() {
    glUseProgram(programId);
    glBindVertexArray(this->vao);

    for (int i = 0; i < text.size(); i++) {
        Character* ch = TextLib::getChar(text[i]);

        glBindTexture(GL_TEXTURE_2D, ch->textureId);
        glDrawArrays(GL_TRIANGLES, i * 6, 6);
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}