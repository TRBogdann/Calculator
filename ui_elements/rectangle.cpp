#include "rectangle.h"


    Rectangle::Rectangle(Math::vec2f _position,float width, float height,Math::vec4f _color):
    position(_position),origin(_position)
    {

    color.x=_color.x;
    color.y=_color.y;
    color.z=_color.z;
    color.k=_color.k;
        
    coord[0]=position+Math::vec2f({-width/2.0f,height/2.0f});
    coord[1]=position+Math::vec2f({-width/2.0f,-height/2.0f});
    coord[2]=position+Math::vec2f({width/2.0f,height/2.0f});
    coord[3]=position+Math::vec2f({width/2.0f,-height/2.0f});


/*
    Math::vec3f normal[4] = {
        utils::convertToGlCoords({coord[0].x, coord[0].y, 0.0f},
                                 window.getWidth(), window.getHeight()),
        utils::convertToGlCoords({coord[1].x, coord[1].y, 0.0f},
                                 window.getWidth(), window.getHeight()),
        utils::convertToGlCoords({coord[2].x, coord[2].y, 0.0f},
                                 window.getWidth(), window.getHeight()),
        utils::convertToGlCoords({coord[3].x, coord[3].y, 0.0f},
                                 window.getWidth(), window.getHeight()),
    };

float data[]
{
    normal[0].x,normal[0].y,1.0f,texCoord[0].x,texCoord[0].y,
    normal[1].x,normal[1].y,1.0f,texCoord[1].x,texCoord[1].y,
    normal[2].x,normal[2].y,1.0f,texCoord[2].x,texCoord[2].y,
    normal[3].x,normal[3].y,1.0f,texCoord[3].x,texCoord[3].y
};
*/



    };

Rectangle::~Rectangle()
{

}

void Rectangle::copyToBuffer(VertexBuffer &buff,float width,float height)
{
  
    Math::vec3f normal[4] = {
        utils::convertToGlCoords({coord[0].x, coord[0].y, 0.0f},
                                 width, height),
        utils::convertToGlCoords({coord[1].x, coord[1].y, 0.0f},
                                 width, height),
        utils::convertToGlCoords({coord[2].x, coord[2].y, 0.0f},
                                 width, height),
        utils::convertToGlCoords({coord[3].x, coord[3].y, 0.0f},
                                 width, height),
    };

float data[]
{
    normal[0].x,normal[0].y,1.0f, color.x,color.y,color.z,color.k,
    normal[1].x,normal[1].y,1.0f, color.x,color.y,color.z,color.k,
    normal[2].x,normal[2].y,1.0f, color.x,color.y,color.z,color.k,
    normal[3].x,normal[3].y,1.0f, color.x,color.y,color.z,color.k,
};

buff.update(data,28*sizeof(float));
};


void Rectangle::setColor(Math::vec4f _color)
{
    this->color.x=_color.x;
    this->color.y=_color.y;
    this->color.z=_color.z;
    this->color.k=_color.k;
}


