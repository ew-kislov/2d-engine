#pragma once

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

namespace OpenglUtils {
    void setUniformMat4(GLuint programId, string name, glm::mat4 matrix) {
        GLuint MatrixId = glGetUniformLocation(programId, name.c_str());
        glUniformMatrix4fv(MatrixId, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void setUniformMat4(GLuint programId, string name, GLfloat* matrix) {
        GLuint MatrixId = glGetUniformLocation(programId, name.c_str());
        glUniformMatrix4fv(MatrixId, 1, GL_FALSE, matrix);
    }
}