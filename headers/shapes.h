#ifndef SHAPES_H
#define SHAPES_H

#include "glad.h"
#include "VAEBO.h"
#include "shaderClass.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>

enum class ShapeTypes {
    SH_LINE,
    SH_LINES,
    SH_TRAINGLE,
    SH_TRIANGLES
};

/// @brief State of the shape
enum class ShapeState {
    STATIC           =       0x0,
    CREATING,
    MODIFYING,

    CURRENT
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
        virtual ~Shape() = default;

        virtual void Draw() {}
        //virtual ~Shape() {}
        virtual void Delete() {}
        virtual void setName(std::string name) {}
        virtual std::string getName() {}
        virtual std::vector<GLfloat> getVertices() { return vertices; }
        virtual void addVertices(GLfloat* addVertices, int addVerticesNum);
        virtual std::vector<GLuint> getIndices() { return indices; }
        virtual void addIndices(GLuint* addIndices, int addIndicesNum);
        virtual void setState(ShapeState shapeState) { state = shapeState; }
        virtual ShapeState getState() { return state; }
        virtual void setType(ShapeTypes shapeType) { type = shapeType; }
        virtual ShapeTypes getType() { return type; }
        virtual void setVBO(VBO* shapeVBO) { vbo = shapeVBO; }
        virtual VBO* getVBO() { return vbo; }
        virtual EBO* getEBO() { return ebo; }
        virtual VAO* getVAO() { return vao; }
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

        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;
        
        GLuint vertexNumber;
        GLuint indicesNumber;

        std::string widgetName = "ciao";

        ShapeState state;

        ShapeTypes type;


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
        ~Line() {};

        void Draw() override;
        void Delete() override;
        std::string getName() override { return "ciaoLi"; }
        //GLfloat* getVertices() const override { return vertices; }
};

class Lines : public Shape
{
    public:
        Lines(GLfloat* _vertices, GLsizeiptr _vertSize, GLuint* _indices, GLsizeiptr _indSize, ShaderFiles shaderFiles);
        ~Lines() {};

        void Draw() override;
        void Delete() override;
        void setName(std::string name) override;
        std::string getName() override { return widgetName; }
};

#endif