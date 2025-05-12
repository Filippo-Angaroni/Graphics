#include "shapes.h"
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void SaveShape(ShapeStruct shapeStruct)
{
    FILE* file;

    file = fopen("./ciao.shp", "w+");

    //Save the shape type
    fwrite(&shapeStruct.shapeType, sizeof(int), 1, file);

    //Save the vertices num and then the array
    fwrite(&shapeStruct.verticesNum, sizeof(int), 1, file);
    fwrite(shapeStruct.vertices, sizeof(float), shapeStruct.verticesNum, file);

    fclose(file);

    FILE* file2;

    file2 = fopen("./ciao.shp", "r+");

    // //Save the vertices num and then the array

    ShapeStruct shStr;

    fread(&shStr.shapeType, sizeof(int), 1, file2);

    //std::cout << static_cast<std::underlying_type<ShapeTypes>::type>(shStr.shapeType) << std::endl;

    fread(&shStr.verticesNum, sizeof(int), 1, file2);
    
    shStr.vertices = new float[shStr.verticesNum]; 

    fread(shStr.vertices, sizeof(float), shStr.verticesNum, file2);

    fclose(file2);

    for (int i = 0; i < 9; i++){
        std::cout << shStr.vertices[i] << " ";
    }

    //std::cout << std::endl;

};

#pragma region Shape

Shape::Shape()
{
    state = ShapeState::STATIC;
}

void Shape::addVertices(GLfloat* addVertices, int addVerticesNum) 
{
    for (int i = 0; i < addVerticesNum; i++) {
        vertices.push_back(addVertices[i]);
    }
    vertexNumber += addVerticesNum;
}

void Shape::addIndices(GLuint* addIndices, int addIndicesNum) 
{
    for (int i = 0; i < addIndicesNum; i++) {
        indices.push_back(addIndices[i]);
    }
    indicesNumber += addIndicesNum;
}

// void Shape::Translate(glm::vec3 delta)
// {
//     transform = glm::translate(transform, delta);
//     glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));
// }

#pragma endregion

#pragma region Triangle

Triangle::Triangle(GLfloat* vertices, GLsizeiptr vertSize, GLuint* indices, GLsizeiptr indSize, ShaderFiles shaderFiles)
{
    shader = new Shader(shaderFiles);

    vao = new VAO();

    vao->Bind();

    vbo = new VBO(vertices, vertSize);
    ebo = new EBO(indices, indSize);

    vao->LinkVBO(*vbo, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
    vao->LinkVBO(*vbo, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();
}

void Triangle::Draw()
{
    shader->Activate();
    vao->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Triangle::Delete()
{
    vao->Delete();
    vbo->Delete();
    ebo->Delete();
    shader->Delete();
}

#pragma endregion

#pragma region Line

Line::Line(GLfloat* vertices, ShaderFiles shaderFiles)
{
    shader = new Shader(shaderFiles);

    vao = new VAO();
    vao->Bind();

    vbo = new VBO(vertices, sizeof(GLfloat) * 6);
    
    vao->LinkVBO(*vbo, 0, 2, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);

    vao->Unbind();
    vbo->Unbind();
}

void Line::Draw()
{
    shader->Activate();

    vao->Bind();

    glDrawArrays(GL_LINE_STRIP, 0, 2);

}

void Line::Delete()
{
    vao->Delete();
    vbo->Delete();
    shader->Delete();
}

#pragma endregion

#pragma region Lines

Lines::Lines(GLfloat* _vertices, GLsizeiptr _vertSize, GLuint* _indices, GLsizeiptr _indSize, ShaderFiles shaderFiles) : Shape()
{
    std::cout << "Initialized" << std::endl;

    std::cout << _vertices[0] << std::endl;

    vertexNumber = _vertSize / sizeof(GLfloat) / 3;
    indicesNumber = _indSize / sizeof(GLuint);

    for (int i = 0; i < vertexNumber * 3; i++){
        vertices.push_back(_vertices[i]);
    }

    for (int i = 0; i < indicesNumber; i++){
        indices.push_back(_indices[i]);
    }

    shader = new Shader(shaderFiles);

    vao = new VAO();

    vao->Bind();

    vbo = new VBO(vertices.data(), _vertSize);
    ebo = new EBO(indices.data(), _indSize);

    vao->LinkVBO(*vbo, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);
    
    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();

    transformLocation = glGetUniformLocation(shader->ID, "transform");
    transform = glm::mat4(1.0f);

    type = ShapeTypes::SH_LINES;

}

void Lines::Draw()
{
    
    //std::cout << "-----------" << std::endl;

    shader->Activate();
    
    //transform = glm::translate(transform, glm::vec3(0.001f));

    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, glm::value_ptr(transform));

    vao->Bind();

    glDrawElements(GL_LINE_STRIP, vertexNumber, GL_UNSIGNED_INT, 0);
}

void Lines::Delete()
{
    vao->Delete();
    vbo->Delete();
    ebo->Delete();
    shader->Delete();
}

void Lines::setName(std::string name)
{
    widgetName = name; 
    std::cout << "Name changed: " << widgetName << std::endl;
}

#pragma endregion

