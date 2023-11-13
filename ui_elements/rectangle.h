#pragma once
#include "../../MyEngine/math_engine/PSBmath.h"
#include "../../MyEngine/graphic_engine/buffers/buffers.h"
#include "../../MyEngine/graphic_engine/transformations/transformations.h"

class Rectangle
{
    public:
    Math::vec2f coord[4];
    Math::vec4f color;
    Math::vec2f origin;
    Math::vec2f position;
    
  Rectangle(Math::vec2f _position,float width, float height,Math::vec4f _color);
  ~Rectangle();
  void setColor(Math::vec4f _color);
  void copyToBuffer(VertexBuffer &buff,float width,float height);


    private:

   

};