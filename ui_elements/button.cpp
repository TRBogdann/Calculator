#include "button.h"
#include "font.h"
#include "rectangle.h"


Button::Button(Math::vec2f _position,float width, float height,Math::vec4f _color,std::string path_to_font,char _character):
buttonArea(Rectangle(_position,width,height,_color)),
font(Character(_position,height,height)),
texture(Texture(path_to_font,0,1)),
character(_character),pressedColor(_color),normalColor(_color),selected(0)
{
    
};

Button::~Button()
{

}

void Button::setColor(Math::vec4f _color,unsigned int number)
{
    if(number!=1 && number!=2)
        return;
    if(number==1)
    {
        normalColor.x=_color.x;
        normalColor.y=_color.y;
        normalColor.z=_color.z;
        normalColor.k=_color.k;
        return;
    }

        pressedColor.x=_color.x;
        pressedColor.y=_color.y;
        pressedColor.z=_color.z;
        pressedColor.k=_color.k;

}

void Button::drawArea(Shader &sh,VertexArray &arr,VertexBuffer &buff,IndexBuffer &ind,Renderer &renderer,float width,float height)
{
    buttonArea.copyToBuffer(buff,width, height);
    renderer.drawType1(arr,ind,sh);
}

void Button::drawFont(Shader &sh,VertexArray &arr,VertexBuffer &buff,IndexBuffer &ind,Renderer &renderer,float width,float height)
{
    font.copyToBuffer(buff, width,height);
    texture.bind();
    renderer.drawType1(arr,ind,sh);
}

//0 max height
//0 min width
//3 min height
//3 min width

bool Button::intersects(Math::vec2f coordinates)
{
   if(coordinates.x<buttonArea.coord[0].x || coordinates.x>buttonArea.coord[3].x)
   {
    if(selected==1){
        buttonArea.setColor(normalColor);
        selected=0;
    }
    
    return 0;
   }
   if(coordinates.y>buttonArea.coord[0].y || coordinates.y<buttonArea.coord[3].y)
    {
    if(selected==1){
     buttonArea.setColor(normalColor);
     selected=0;
    }
    return 0;
   }

    if(selected==0){
    buttonArea.setColor({0.0f,0.0f,1.0f,1.0f});
    selected=1;
    }
    
    return 1;
};

bool Button::isSelected()
{
    return this->selected;
}