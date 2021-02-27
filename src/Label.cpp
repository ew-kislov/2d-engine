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
}

void Label::transform() {
    glm::mat4 cameraMatrix = Camera::getResultMatrix();
    this->applyTransformationMatrix(cameraMatrix * this->positionMatrix);
}

void Label::setPreview() {
    TextLib::initFont(fontSource, this->size);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
}

void Label::draw() {
    glUseProgram(programId);
    glUniform3f(glGetUniformLocation(programId, "textColor"), color.x, color.y, color.z);
    // glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    float x = this->position.x;
    float y = this->position.y;
    
    GLfloat* buffer = new GLfloat[text.size() * 24];
    // cout << "shit 2" << endl;

    for (int i = 0; i < text.size(); i++) 
    {
        Character* ch = TextLib::getChar(text[i]);

        float xpos = x;
        float ypos = y + this->size - ch->bearing.y;

        float w = ch->size.x;
        float h = ch->size.y;
        // update VBO for each character
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
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 24 * text.size() * sizeof(GLfloat), buffer, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    // iterate through all characters
    for (int i = 0; i < text.size(); i++) 
    {
        Character* ch = TextLib::getChar(text[i]);

        float xpos = x;
        float ypos = y + this->size - ch->bearing.y;

        float w = ch->size.x;
        float h = ch->size.y;
        // update VBO for each character
        float vertices[24] = {
             xpos,     ypos + h,   0.0f, 1.0f ,            
             xpos,     ypos,       0.0f, 0.0f ,
             xpos + w, ypos,       1.0f, 0.0f ,

             xpos,     ypos + h,   0.0f, 1.0f ,
             xpos + w, ypos,       1.0f, 0.0f ,
             xpos + w, ypos + h,   1.0f, 1.0f       
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch->textureId);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch->advance >> 6); // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    delete[] buffer;
}