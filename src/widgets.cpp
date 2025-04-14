#include "widgets.h"

ShapeState shapeState = ShapeState::EMPTY;
Tools currentTool = Tools::LINE;
Actions action = Actions::EMPTY;

#pragma region RenderWidget

RenderWidget::RenderWidget(std::string name, ImVec2 size)
{
    fbo = new FBO(size.x, size.y);
    widgetName = name;
    widgetSize = size;
    canva = std::make_unique<Canva>(widgetSize);

    ShapeState shapeState = ShapeState::EMPTY;
    Actions action = Actions::EMPTY;
}

void RenderWidget::registerEvents()
{
    if (ImGui::IsMouseClicked(0)){

        std::cout << ImGui::GetMousePos().x << std::endl;

        ImVec2 relativeMousePos = ImVec2(ImGui::GetMousePos().x - ImGui::GetWindowPos().x, ImGui::GetMousePos().y - ImGui::GetWindowPos().y);

        //Chek if the clicked point is inside the canvas
        if (relativeMousePos.x > 0 && relativeMousePos.x < ImGui::GetWindowWidth()){
            if (relativeMousePos.y > 0 && relativeMousePos.y < ImGui::GetWindowHeight()){
                
                //Detect wich tool is selected
                switch (currentTool)
                {
                    //Check if the current tool is LINE
                    case Tools::LINE:

                        //Check in wich state is the current/selected shape
                        switch (shapeState)
                        {
                            case ShapeState::EMPTY:
                            {



                                ImVec2 mpos = ImVec2(ImGui::GetMousePos().x - ImGui::GetWindowPos().x, ImGui::GetMousePos().y - ImGui::GetWindowPos().y);

                                GLfloat lineVertices[] = {
                                    2 * mpos.x / ImGui::GetWindowWidth() - 1.0f, (-1) * 2 * mpos.y / ImGui::GetWindowHeight() + 1.0f,   0.0f,
                                    0.0f,   0.0f,   0.0f,
                                };

                                GLuint lineIndices[] = {
                                    0, 1
                                };

                                ShaderGenerator shader("ciao");

                                Lines lines(lineVertices, sizeof(lineVertices), lineIndices, sizeof(lineIndices), shader.createShader());
                                lines.setName("bob");
                                action = Actions::EMPTY;
                                std::cout << "Line pointer: " << &lines << std::endl;
                                this->addShape(std::move(lines));
                                std::cout << "Line pointer after: " << canva->shapes[0].get() << std::endl;
                                shapeState = ShapeState::CREATING;
                                
                                break;
                            }

                            case ShapeState::CREATING:
                            {
                                ImVec2 mpos = ImVec2(ImGui::GetMousePos().x - ImGui::GetWindowPos().x, ImGui::GetMousePos().y - ImGui::GetWindowPos().y);

                                

                            }

                            default:
                                break;
                        }

                        break;
                    
                    default:
                        break;
                }
            }
        }
    }   

    switch (shapeState)
    {
        case ShapeState::CREATING:
        {

            //std::cout << currentShapes[0].get()->getName() << std::endl;

            break;
        }
            
        
        default:
            break;
    }

}

void RenderWidget::execEvents()
{
    // switch (action)
    // {
    //     case Actions::CREATE_LINE:
    //     {

            
    //         break;
    //     }
        
    //     default:
    //         break;
    // }
}

void RenderWidget::Draw()
{
    ImGui::Begin(widgetName.c_str());
    ImGui::BeginChild("RenderChild");
    fbo->Bind();
    fbo->RescaleFBO(ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
    glViewport(0, 0, ImGui::GetWindowWidth(), ImGui::GetWindowHeight());
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (canva->shapes.size() > 0)
    {


        for (int i = 0; i < canva->shapes.size(); i++){
            //std::cout << "Ciao " << canva->shapes[i]->getVertices()[0] << std::endl;
            canva->shapes[i]->Draw();
            std::cout << canva->shapes[i]->getName() << std::endl;
        }

        // std::cout << "Shape type: " << typeid(canva->shapes[0]).name() << std::endl;
        // std::cout << "Shape name: " << canva->shapes[0]->getName() << std::endl;
        // for (const auto &shape : canva->shapes)
        // {
        //     //std::cout << "Shape name: " << shape->getName() << std::endl;
            
        //     //glBindBuffer(GL_ARRAY_BUFFER, shape->getVBO()->ID);
        //     //glBufferData(GL_ARRAY_BUFFER, 6 * 4, shape->getVertices(), GL_STATIC_DRAW);
        //     shape->Draw();
        //     std::cout << "Ver: " << shape->getVertices()[0] << std::endl; 
        // }
    }

    fbo->Unbind();
    ImGui::Image((ImTextureID)fbo->getFrameTexture(), ImGui::GetWindowSize(), ImVec2(0, 1), ImVec2(1, 0));
    
    registerEvents();
    execEvents();
    ImGui::EndChild();
    ImGui::End();


}

void RenderWidget::Delete()
{
    fbo->Delete();
    // for (int shapeIndex = 0; shapeIndex < (int)canva->shapes.size(); shapeIndex++)
    // {
    //     canva->shapes[0]->Delete();
    // }
}

void RenderWidget::Resize(ImVec2 size)
{
    widgetSize = size;
} 

#pragma endregion

#pragma region ToolWidget

ToolWidget::ToolWidget(std::string name, ImVec2 size)
{
    widgetName = name;
    widgetSize = size;

    Tools currentTool = Tools::LINE;
}

void ToolWidget::Draw()
{
    ImGui::Begin(widgetName.c_str());

    ImGui::SetWindowSize(widgetSize);

    ImGui::Button("Line");

    ImGui::End();
}

void ToolWidget::Delete()
{

}

void ToolWidget::Resize(ImVec2 size)
{
    widgetSize = size;
}

#pragma endregion