#pragma once

#include "Label.hpp"

#include "TextLib.cpp"
#include "Camera.cpp"
#include "UiElement.cpp"

Label::Label(string text, string fontSource, int size, glm::vec4 color, glm::vec2 position, int layer):
    UiElement("src/label_fragment_shader.glsl", "src/vertex_shader.glsl", position, layer) {
    this->text = text;
    this->fontSource = fontSource;
    this->size = size;
    this->color = color;
}

void Label::init() {
    // init font
    
    TextLib::initFont(fontSource, this->size);

    OpenGL::useProgram(this->programId);

    // init vao

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    // init texture

    GLuint textureCoordVbo;

    GLfloat textureСoordData[12] {
        0.0f, 1.0f,            
        0.0f, 0.0f,
        1.0f, 0.0f,

        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f     
    };

    glGenBuffers(1, &textureCoordVbo);
    glBindBuffer(GL_ARRAY_BUFFER, textureCoordVbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12 * text.size(), NULL, GL_STATIC_DRAW);

    for (int i = 0; i < this->text.size(); i++) {
        glBufferSubData(GL_ARRAY_BUFFER, i * 12 * sizeof(GLfloat), sizeof(GLfloat) * 12, &textureСoordData);
    }

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    this->vbos[VboType::TextureCoords] = textureCoordVbo;

    // init vertices

    GLfloat z = 1.0 * this->layer / MAX_LAYERS + MIN_Z;

    GLuint positionVbo;

    glGenBuffers(1, &positionVbo);
    glBindBuffer(GL_ARRAY_BUFFER, positionVbo);

    this->vbos[VboType::Position] = positionVbo;

    float x = this->position.x;
    float y = this->position.y;
    
    GLfloat* buffer = new GLfloat[text.size() * 18];

    for (int i = 0; i < text.size(); i++) {
        Character* ch = TextLib::getChar(text[i]);

        float xpos = x;
        float ypos = y + this->size - ch->bearing.y;

        float w = ch->size.x;
        float h = ch->size.y;

        GLfloat* vertices = new GLfloat[18] {
             xpos,     ypos + h, z,          
             xpos,     ypos,     z,
             xpos + w, ypos,     z,

             xpos,     ypos + h, z,
             xpos + w, ypos,     z,
             xpos + w, ypos + h, z    
        };

        memcpy(buffer + i * 18, vertices, 18 * sizeof(GLfloat));

        delete[] vertices;

        x += (ch->advance >> 6);
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18 * text.size(), buffer, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

    delete[] buffer;

    // init color 

    glUniform3f(glGetUniformLocation(programId, "text_color"), color.x, color.y, color.z);
}

void Label::draw() {
    OpenGL::useProgram(this->programId);
    glBindVertexArray(this->vao);

    for (int i = 0; i < text.size(); i++) {
        Character* ch = TextLib::getChar(text[i]);

        OpenGL::bindTexture(ch->textureId);
        glDrawArrays(GL_TRIANGLES, i * 6, 6);
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

string Label::getClassId() {
    return "Label";
}