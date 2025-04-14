#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

typedef struct {
    const char* vertexFile;
    const char* fragmentFile;
} ShaderFiles;

std::string get_file_contents(const char* file_name);

class Shader
{
    public:
        GLuint ID;
        Shader(const char* vertexFile, const char* fragmentFile);
        Shader(ShaderFiles shaderFiles);

        void Activate();
        void Delete();
        void InitShader(const char* vertexFile, const char* fragmentFile);
};

#endif