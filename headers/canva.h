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



class Canva
{
    public:
        Canva(ImVec2 size);
        template <typename T>
        void addShape(T shape)
        {
            shapes.push_back(std::move(shape));
            //std::cout << shape.name << " Size" << std::endl;
        }
        std::vector<std::unique_ptr<Shape>> shapes;
        
};

#endif