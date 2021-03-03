#pragma once

#include "OpenGL.hpp"

map<string, GLuint> OpenGL::programs = {};
GLuint OpenGL::activeProgram = -1;
GLuint OpenGL::activeTexture = -1;
GLuint OpenGL::activeVao = -1;

GLuint OpenGL::createProgram(char *vertexShaderSource, char *fragmentShaderSource) {
    string shadersString = string(vertexShaderSource) + string(fragmentShaderSource);
    GLuint cachedProgramId = OpenGL::programs[shadersString];
    if (cachedProgramId) {
        return cachedProgramId;
    }

    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    string vertexShaderCode;
    ifstream vertexShaderStream(vertexShaderSource, ios::in);

    if (vertexShaderStream.is_open()) {
        stringstream sstr;
        sstr << vertexShaderStream.rdbuf();
        vertexShaderCode = sstr.str();
        vertexShaderStream.close();
    } else {
        fprintf(stderr, "Error: can't open %s.", vertexShaderSource);
        exit(1);
    }

    string fragmentShaderCode;
    ifstream fragmentShaderStream(fragmentShaderSource, ios::in);

    if (fragmentShaderStream.is_open()) {
        stringstream sstr;
        sstr << fragmentShaderStream.rdbuf();
        fragmentShaderCode = sstr.str();
        fragmentShaderStream.close();
    } else {
        fprintf(stderr, "Error: can't open %s.", vertexShaderSource);
        exit(1);
    }

    GLint result = GL_FALSE;
    int infoLogLength;

    // printf("Compiling shader: %s\n", vertexShaderSource);
    const char *vertexSourcePointer = vertexShaderCode.c_str();
    glShaderSource(vertexShaderId, 1, &vertexSourcePointer, NULL);
    glCompileShader(vertexShaderId);

    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        vector<char> vertexShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(vertexShaderId, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
        printf("%s\n", &vertexShaderErrorMessage[0]);
    }

    // printf("Compiling shader: %s\n", fragmentShaderSource);
    const char *fragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderId, 1, &fragmentSourcePointer, NULL);
    glCompileShader(fragmentShaderId);

    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
        glGetShaderInfoLog(fragmentShaderId, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
        printf("%s\n", &fragmentShaderErrorMessage[0]);
    }

    // printf("Linking program\n");
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    glGetProgramiv(programId, GL_LINK_STATUS, &result);
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0) {
        vector<char> ProgramErrorMessage(infoLogLength + 1);
        glGetProgramInfoLog(programId, infoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    OpenGL::programs[shadersString] = programId;

    return programId;
}

void OpenGL::useProgram(GLuint id) {
    if (id != OpenGL::activeProgram) {
        cout << "changing shader " << id << endl;
        glUseProgram(id);
        OpenGL::activeProgram = id;
    }
}

void OpenGL::bindTexture(GLuint id) {
    if (id != OpenGL::activeTexture) {
        glBindTexture(GL_TEXTURE_2D, id);
        OpenGL::activeTexture = id;
    }
}

void OpenGL::bindVao(GLuint id) {
    if (id != OpenGL::activeVao) {
        glBindVertexArray(id);
        OpenGL::activeVao = id;
    }
}