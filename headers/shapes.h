#ifndef SHAPES_H
#define SHAPES_H

#include "glad.h"
#include "VAEBO.h"
#include "shaderClass.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

enum class ShapeTypes {
    SH_LINE,
    SH_LINES,
    SH_TRAINGLE,
    SH_TRIANGLES
};

#pragma region ShapeStructure

typedef struct 
{
    ShapeTypes shapeType;
    GLuint verticesNum;
    GLfloat* vertices;

} ShapeStruct;

#pragma endregion

void SaveShape(ShapeStruct shapeStruct);

class Shape
{
    public:
        Shape();

        virtual void Draw() {}
        //virtual ~Shape() {}
        virtual void Delete() {}
        virtual void setName(std::string name) {}
        virtual std::string getName() {}
        virtual GLfloat* getVertices() { return vertices.get(); }
        virtual GLuint* getIndices() { return indices.get(); }
        // virtual void Rotate() = 0;
        // virtual void Translate(glm::vec3 delta) = 0;

    protected:
        Shader* shader;
        VAO* vao;
        VBO* vbo;
        EBO* ebo;
        FBO* fbo;

        GLuint transformLocation;
        glm::mat4 transform;

        std::unique_ptr<GLfloat[]> vertices;
        std::unique_ptr<GLuint[]> indices;
        
        GLuint vertexNumber;
        GLuint indicesNumber;

        std::string widgetName = "ciao";

};

class Triangle : public Shape
{
    public:
        Triangle(GLfloat* vertices, GLsizeiptr vertSize, GLuint* indices, GLsizeiptr indSize, ShaderFiles shaderFiles);
        //~Triangle() override {}

        void Draw() override;
        void Delete() override;
        std::string getName() override { return widgetName; }
        //GLfloat* getVertices() const override { return vertices; }

};

class Line : public Shape
{
    public:
        Line(GLfloat* vertices, ShaderFiles shaderFiles);
        //~Line() override {}

        void Draw() override;
        void Delete() override;
        std::string getName() override { return "ciaoLi"; }
        //GLfloat* getVertices() const override { return vertices; }
};

class Lines : public Shape
{
    public:
        Lines(GLfloat* _vertices, GLsizeiptr _vertSize, GLuint* _indices, GLsizeiptr _indSize, ShaderFiles shaderFiles);

        void Draw() override;
        void Delete() override;
        void setName(std::string name) override;
        std::string getName() override { return widgetName; }

};

#endif