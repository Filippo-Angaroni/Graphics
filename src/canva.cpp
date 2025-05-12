#include "canva.h"

Canva::Canva(ImVec2 size) 
{

}

void Canva::Clean() {
    // for (int i = 0; i < shapes.size(); i++) {
    //     delete (Shape*)shapes[i].get();
    // }

    shapes.clear();
    currentShapesIndices.clear();

}
