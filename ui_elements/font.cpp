#include "font.h"

  

Character::Character()
{

    this->position={0.0f,0.0f};
    this->origin={0.0f,0.0f};
    texCoord[0]={0.0f,0.0f};
    texCoord[2]={1.0f,0.0f};
    texCoord[1]={0.0f,1.0f};
    texCoord[3]={1.0f, 1.0f};
    coord[0]={0.0f,0.0f};
    coord[2]={0.0f,0.0f};
    coord[1]={0.0f,0.0f};
    coord[3]={0.0f,0.0f};
};

Character::Character(Math::vec2f _position,float width, float height):
    position(_position),origin(_position)
    {


        
    coord[0]=position+Math::vec2f({-width/2.0f,height/2.0f});
    coord[1]=position+Math::vec2f({-width/2.0f,-height/2.0f});
    coord[2]=position+Math::vec2f({width/2.0f,height/2.0f});
    coord[3]=position+Math::vec2f({width/2.0f,-height/2.0f});

    texCoord[0]={0.0f,0.0f};
    texCoord[2]={1.0f,0.0f};
    texCoord[1]={0.0f,1.0f};
    texCoord[3]={1.0f, 1.0f};

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

Character& Character::operator=(const Character& character)
{
    for(int i=0;i<4;i++)
    {
        this->coord[i]=character.coord[i];
        this->texCoord[i]=character.texCoord[i];
    }
    this->origin=character.origin;
    this->position=character.position;

    return *this;
}

Character::~Character()
{

};

  void Character::copyToBuffer(VertexBuffer &buff,float width,float height)
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
   
    normal[0].x,normal[0].y,1.0f,texCoord[0].x,texCoord[0].y,
    normal[1].x,normal[1].y,1.0f,texCoord[1].x,texCoord[1].y,
    normal[2].x,normal[2].y,1.0f,texCoord[2].x,texCoord[2].y,
    normal[3].x,normal[3].y,1.0f,texCoord[3].x,texCoord[3].y
};

buff.update(data,20*sizeof(float));
};


