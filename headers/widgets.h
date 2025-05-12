#ifndef WIDGETS_CLASS_H
#define WIDGETS_CLASS_H

#include "glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include <memory>
#include "shaderClass.h"
#include "shaderGenerator.h"
#include "shapes.h"
#include "VAEBO.h"
#include "imgui.h"
#include "canva.h"

enum class Tools {
    LINE
};



enum class Actions {
    EMPTY,
    CREATE_LINE
};

extern Tools currentTool;
extern ShapeState shapeState;
extern Actions action;

extern std::shared_ptr<Canva> currentCanva;

class RenderWidget 
{
    public:
        RenderWidget(std::string name, ImVec2 size);

        void Draw();
        void Resize(ImVec2 size);
        void Delete();
        template <typename T>
        void addShape(T shape, ShapeState shpState = ShapeState::STATIC)
        {
            canva->addShape(shape);
            //std::cout << shape.getVertex(0) << std::endl;
            //std::cout << "Name: " << canva->shapes[0]->getName() << std::endl;
        }
        void registerEvents();
        void execEvents();

    //private:
        std::string widgetName; 
        FBO* fbo;
        ImVec2 widgetSize;
        std::shared_ptr<Canva> canva;
};

class ToolWidget
{
    public:
        ToolWidget(std::string name, ImVec2 size);

        void Draw();
        void Resize(ImVec2 size);
        void Delete();
    
    private:
        std::string widgetName;
        ImVec2 widgetSize;
};

#endif