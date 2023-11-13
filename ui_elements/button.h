#pragma once
#include "rectangle.h"
#include "font.h"
#include "../../MyEngine/graphic_engine/textures/texture.h"
#include "../../MyEngine/graphic_engine/renderer/renderer.h"
#include "../../MyEngine/graphic_engine/windows/window.h"

class Button
{
    public:
    Button(Math::vec2f _position,float width, float height,Math::vec4f _color,std::string font,char _character);
    ~Button();
    void setColor(Math::vec4f _color,unsigned int number=1);
    void drawArea(Shader &sh,VertexArray &arr,VertexBuffer &buff,IndexBuffer &ind,Renderer &renderer,float width,float heigh);
    void drawFont(Shader &sh,VertexArray &arr,VertexBuffer &buff,IndexBuffer &ind,Renderer &renderer,float width,float heigh);
    bool intersects(Math::vec2f coords);
    bool isSelected();

    private:
    Texture texture;
    Rectangle buttonArea;
    Character font; 
    Math::vec4f normalColor;
    Math::vec4f pressedColor;
    bool selected=0;
    char character;
};