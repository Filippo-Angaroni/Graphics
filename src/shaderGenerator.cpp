#include "shaderGenerator.h"
#include <iostream>
#include <fstream>
#include <string>

ShaderGenerator::ShaderGenerator(std::string fileName)
{

    shaderName = fileName;

    std::ofstream vertFile(fileName + ".vert");

    vertFile << defaultVertVersion      +
                defaultVertLayout       +
                defaultVertTransform    +
                defaultVertMain         +
                defaultVertPosition     +
                defaultVertClosing;

    vertFile.close();

    std::ofstream fragFile(fileName + ".frag");

    fragFile << defaultFragVersion  +
                defaultFragOut      +
                defaultFragMain     +
                defaultFragColor    +
                defaultFragClosing;

    fragFile.close();

}

ShaderFiles ShaderGenerator::createShader()
{
    ShaderFiles shaderFile;
    std::string vertFileName = "./" + shaderName + ".vert";
    std::string fragFileName = "./" + shaderName + ".frag";
    shaderFile.vertexFile = vertFileName.c_str();
    shaderFile.fragmentFile = fragFileName.c_str();
    return shaderFile;
}