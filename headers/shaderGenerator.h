#ifndef SHADER_GENERATOR_H
#define SHADER_GENERATOR_H

#include <string> 
#include "shaderClass.h"

class ShaderGenerator 
{
    public:
        ShaderGenerator(std::string fileName);
        ShaderFiles createShader();

    private:

        std::string shaderName;

        #pragma region Vertex Shader
        std::string defaultVertVersion = "#version 330 core\n";
        std::string defaultVertLayout = "layout (location = 0) in vec3 aPos;\n";
        std::string defaultVertTransform = "uniform mat4 transform;\n";
        std::string defaultVertMain = "void main()\n{\n";
        std::string defaultVertPosition = "\tgl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n";
        std::string defaultVertClosing = "}\0";
        #pragma endregion

        #pragma region Fragment Shader

        std::string defaultFragVersion = defaultVertVersion;
        std::string defaultFragOut = "out vec4 FragColor;\n";
        std::string defaultFragMain = defaultVertMain;
        std::string defaultFragColor = "\tFragColor = vec4(0.24, 1.0, 0.0, 1.0);\n";
        std::string defaultFragClosing = defaultVertClosing;
        #pragma endregion

};

#endif