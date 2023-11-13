#pragma once
#include "../../MyEngine/math_engine/PSBmath.h"
#include "../../MyEngine/graphic_engine/buffers/buffers.h"
#include "../../MyEngine/graphic_engine/transformations/transformations.h"

class Character
{
    public:
    Math::vec2f coord[4];
    Math::vec2f texCoord[4];
    Math::vec2f origin;
    Math::vec2f position;

    Character();
    Character(Math::vec2f _position,float width, float height);
    Character& operator=(const Character& character);
    ~Character();

  void copyToBuffer(VertexBuffer &buff,float width,float height);


/*
void draw(Renderer &renderer,Shader *shader)
{


}
*/
    private:

   

};
