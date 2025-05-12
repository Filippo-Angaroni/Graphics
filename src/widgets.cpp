#include "widgets.h"

Tools currentTool = Tools::LINE;
Actions action = Actions::EMPTY;
std::shared_ptr<Canva> currentCanva;

#pragma region RenderWidget

RenderWidget::RenderWidget(std::string name, ImVec2 size)
{
    fbo = new FBO(size.x, size.y);
    widgetName = name;
    widgetSize = size;
    canva = std::make_shared<Canva>(widgetSize);
    currentCanva = canva;

    Actions action = Actions::EMPTY;
}

void RenderWidget::registerEvents()
{

    if (!canva->shapes.size());

    //Mouse Click
    if (ImGui::IsMouseClicked(0)){

        ImVec2 relativeMousePos = ImVec2(ImGui::GetMousePos().x - ImGui::GetWindowPos().x, ImGui::GetMousePos().y - ImGui::GetWindowPos().y);

        //Chek if the clicked point is inside the canvas
        if (relativeMousePos.x > 0 && relativeMousePos.x < ImGui::GetWindowWidth()){
            if (relativeMousePos.y > 0 && relativeMousePos.y < ImGui::GetWindowHeight()){
                
                //Detect which tool is selected
                switch (currentTool)
                {
                    //Check if the current tool is LINE
                    case (Tools::LINE): 
                    {
                        //If the current shape size = 0 then initialize the line
                        if (canva->currentShapesIndices.size() == 0) {

                            ImVec2 mpos = ImVec2(ImGui::GetMousePos().x - ImGui::GetWindowPos().x, ImGui::GetMousePos().y - ImGui::GetWindowPos().y);

                            GLfloat* lineVertices = new GLfloat[3]{
                                2 * mpos.x / ImGui::GetWindowWidth() - 1.0f, (-1) * 2 * mpos.y / ImGui::GetWindowHeight() + 1.0f,   0.0f
                            };

                            GLuint* lineIndices = new GLuint[1]{ 0 };

                            ShaderGenerator shader("ciao");

                            Lines* lines = new Lines(lineVertices, sizeof(lineVertices), lineIndices, sizeof(lineIndices), shader.createShader());
                            //lines->setName("bob");
                            action = Actions::EMPTY;
                            std::cout << "Line pointer: " << &lines << std::endl;
                            lines->setState(ShapeState::CREATING);
                            this->addShape(std::make_shared<Lines>((Lines)*lines));
                            std::cout << "Shape state: " << (int)lines->getState() << std::endl;

                            delete[] lineVertices; 
                            delete[] lineIndices;

                            break;

                        }

                        //Check in wich state is the current/selected shape
                        switch (canva->shapes[0].get()->getState())
                        {
                            case ShapeState::STATIC:
                            {                 
                                break;
                            }

                            //Get current mouse position, create the new vertex and index, update VBO and EBO
                            case ShapeState::CREATING:
                            {
                                ImVec2 mpos = ImVec2(ImGui::GetMousePos().x - ImGui::GetWindowPos().x, ImGui::GetMousePos().y - ImGui::GetWindowPos().y);

                                GLfloat* newVertex = new GLfloat[3]{
                                    (2 * mpos.x / ImGui::GetWindowWidth() - 1.0f),
                                    (-1) * 2 * mpos.y / ImGui::GetWindowHeight() + 1.0f,
                                    0.0f
                                };

                                GLuint* newIndex = new GLuint[1] { 
                                    (canva->shapes[0].get()->getIndices().size())
                                };

                                int currentShapeIndex = canva->currentShapesIndices[0];

                                canva->shapes[currentShapeIndex].get()->addVertices(newVertex, 3);
                                canva->shapes[currentShapeIndex].get()->addIndices(newIndex, 1);

                                glBindVertexArray(canva->shapes[0].get()->getVAO()->ID);

                                glBindBuffer(GL_ARRAY_BUFFER, canva->shapes[0].get()->getVBO()->ID);
                                glBufferData(GL_ARRAY_BUFFER, canva->shapes[0].get()->getVertices().size() * sizeof(GLfloat), canva->shapes[0].get()->getVertices().data(), GL_DYNAMIC_DRAW);

                                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, canva->shapes[0].get()->getEBO()->ID);
                                glBufferData(GL_ELEMENT_ARRAY_BUFFER, canva->shapes[0].get()->getIndices().size() * sizeof(GLuint), canva->shapes[0].get()->getIndices().data(), GL_DYNAMIC_DRAW);

                                glBindVertexArray(0);

                                delete[] newVertex;
                                delete[] newIndex;

                                break;

                            }

                            default:
                                break;
                        }

                        break;
                    }
                    default:
                        break;
                }
            }
        }
    }   

    for (int shapeIndex = 0; shapeIndex < canva->getShapesNum(); shapeIndex++){

        switch (canva->getShapeType(shapeIndex))
        {
            case ShapeTypes::SH_LINES:
            {
                
                switch (canva->getShapeState(shapeIndex))
                {
                    case ShapeState::STATIC:
                        break;
                    
                    case ShapeState::CREATING: 
                    {
                        ImVec2 mpos = ImVec2(ImGui::GetMousePos().x - ImGui::GetWindowPos().x, ImGui::GetMousePos().y - ImGui::GetWindowPos().y);

                        GLfloat* newVertex = new GLfloat[3]{
                            (2 * mpos.x / ImGui::GetWindowWidth() - 1.0f),
                            (-1) * 2 * mpos.y / ImGui::GetWindowHeight() + 1.0f,
                            0.0f
                        };

                        GLuint* newIndex = new GLuint[1] { 
                            (canva->shapes[0].get()->getIndices().size())
                        };

                        int currentShapeIndex = canva->currentShapesIndices[0];

                        canva->shapes[currentShapeIndex].get()->addVertices(newVertex, 3);
                        canva->shapes[currentShapeIndex].get()->addIndices(newIndex, 1);

                        glBindVertexArray(canva->shapes[0].get()->getVAO()->ID);

                        glBindBuffer(GL_ARRAY_BUFFER, canva->shapes[0].get()->getVBO()->ID);
                        glBufferData(GL_ARRAY_BUFFER, canva->shapes[0].get()->getVertices().size() * sizeof(GLfloat), canva->shapes[0].get()->getVertices().data(), GL_DYNAMIC_DRAW);

                        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, canva->shapes[0].get()->getEBO()->ID);
                        glBufferData(GL_ELEMENT_ARRAY_BUFFER, canva->shapes[0].get()->getIndices().size() * sizeof(GLuint), canva->shapes[0].get()->getIndices().data(), GL_DYNAMIC_DRAW);

                        glBindVertexArray(0);

                        delete[] newVertex;
                        delete[] newIndex;

                        break;
                    }

                    default:
                        break;
                }

                break;
            }
            default:
                break;
        }

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
            canva->shapes[i]->Draw();
        }
    }

    registerEvents();
    fbo->Unbind();
    ImGui::Image((ImTextureID)fbo->getFrameTexture(), ImGui::GetWindowSize(), ImVec2(0, 1), ImVec2(1, 0));
    
    execEvents();
    ImGui::EndChild();
    ImGui::End();
}

void RenderWidget::Delete()
{
    fbo->Delete();
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

    if (ImGui::Button("Clean Canva")) {
        if (currentCanva) {
            currentCanva->Clean();
        }
    }

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