#ifndef CANVA_CLASS_H
#define CANVA_CLASS_H

#include "glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "shaderClass.h"
#include "shaderGenerator.h"
#include "shapes.h"
#include "VAEBO.h"
#include "imgui.h"
#include <memory>
#include <string>
#include <vector>


class Canva
{
    public:
        Canva(ImVec2 size);

        /// @brief Clean the canva from all shapes
        void Clean();

        /// @brief Set the name of the shape at the 'index' position in the shapes vector.
        /// @param index 
        /// @param name 
        void setShapeName(int index, std::string name) { shapes[index].get()->setName(name); }

        /// @brief Get the shape name of the shape at the 'index' position in the shapes vector.
        /// @param index 
        /// @return 
        std::string getShapeName(int index) { shapes[index].get()->getName(); }

        /// @brief Add vertices to the shape at the 'index' position in the shapes vector
        /// @param index 
        /// @param vertices 
        /// @param verticesNum 
        void addShapeVertices(int index, GLfloat* vertices, int verticesNum) { shapes[index].get()->addVertices(vertices, verticesNum); }

        /// @brief Get the vertices of the shape at the 'index' position in the shapes vector
        /// @param index 
        /// @return 
        std::vector<GLfloat> getShapeVertices(int index) { return shapes[index].get()->getVertices(); }

        /// @brief Add indices to the shape at the 'index' position in the shapes vector
        /// @param index 
        /// @param indices 
        /// @param indicesNum 
        void addShapeIndices(int index, GLuint* indices, int indicesNum) { shapes[index].get()->addIndices(indices, indicesNum); }

        /// @brief Get the indices of the shape at the 'index' position in the shapes vector
        /// @param index 
        /// @return 
        std::vector<GLuint> getShapeIndices(int index) { return shapes[index].get()->getIndices(); }

        /// @brief Set the shape type of the shape at the 'index' position in the shapes vector
        /// @param index 
        /// @param shapeType 
        void setShapeType(int index, ShapeTypes shapeType) { shapes[index].get()->setType(shapeType); }
        
        /// @brief Get the shape type of the shape at the 'index' position in the shapes vector.
        /// @param index 
        /// @return The shape type
        ShapeTypes getShapeType(int index) { return shapes[index].get()->getType(); }
        
        void setShapeState(int index, ShapeState shapeState) { return shapes[index].get()->setState(shapeState); }
        
        /// @brief Get the shape state of the shape at the 'index' position in the shapes vector.
        /// @param index 
        /// @return The shape state
        ShapeState getShapeState(int index) { return shapes[index].get()->getState(); }

        /// @brief Get the number of shapes inside the shapes vector
        /// @return Number of shapes inside shapes vector
        int getShapesNum() { return shapes.size(); }

        /// @brief Get the VBO of the shape at the 'index' position in the shapes vector 
        /// @param index 
        /// @return VBO of the shape
        VBO* getShapeVBO(int index) { return shapes[index].get()->getVBO(); }

        /// @brief Get the EBO of the shape at the 'index' position in the shapes vector
        /// @param index 
        /// @return EBO of the shape
        EBO* getShapeEBO(int index) { return shapes[index].get()->getEBO(); }
        
        /// @brief Get the VAO of the shape at the 'index' position in the shapes vector
        /// @param index 
        /// @return VAO of the shape
        VAO* getShapeVAO(int index) { return shapes[index].get()->getVAO(); }


        /// @brief Add a shape into the shapes vector and update the currentShapesIndices vector
        template <typename T>
        void addShape(T shape)
        {
            shapes.push_back(shape);
            currentShapesIndices.push_back(shapes.size() - 1);
        }

        /// @brief Vector with all the shapes present in the canva
        std::vector<std::shared_ptr<Shape>> shapes;

        /// @brief Indices of the current shpaest inside shapes vector.
        std::vector<int> currentShapesIndices;

        
};

#endif