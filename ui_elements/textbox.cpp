#include "textbox.h"
#include "font.h"

Textbox::Textbox(std::string texturePaths[20],Math::vec2f position,float width):
textures{
Texture(texturePaths[0],0,1),
Texture(texturePaths[1],0,1),
Texture(texturePaths[2],0,1),
Texture(texturePaths[3],0,1),
Texture(texturePaths[4],0,1),
Texture(texturePaths[5],0,1),
Texture(texturePaths[6],0,1),
Texture(texturePaths[7],0,1),
Texture(texturePaths[8],0,1),
Texture(texturePaths[9],0,1),
Texture(texturePaths[10],0,1),
Texture(texturePaths[11],0,1),
Texture(texturePaths[12],0,1),
Texture(texturePaths[13],0,1),
Texture(texturePaths[14],0,1),
Texture(texturePaths[15],0,1),
Texture(texturePaths[16],0,1),
Texture(texturePaths[17],0,1),
Texture(texturePaths[18],0,1),
Texture(texturePaths[19],0,1)}
{
    for (int i=0;i<15;i++)
    {
        positionArray[i]=0;
    }
    Math::vec2f currentPos=position;
    float dimension=width/15;
    box[7]=Character(currentPos,dimension,dimension);
    for(int i=6;i>-1;i--)
    {
        currentPos={currentPos.x-dimension,currentPos.y};
        box[i]=Character(currentPos,dimension,dimension);
 
    }
    currentPos=position;
        for(int i=8;i<15;i++)
    {
        currentPos={currentPos.x+dimension,currentPos.y};
        box[i]=Character(currentPos,dimension,dimension);
    }

 for(int i=0;i<15;i++){
         box[i].texCoord[0]*=0.75f;
        box[i].texCoord[1]*=0.75f;
        box[i].texCoord[2]*=0.75f;
        box[i].texCoord[3]*=0.75f;
  }

}

Textbox::~Textbox()
{

}

int Textbox::charIsUsable(char chr)
{   
    int pos=-1;
    for(int i=0;i<20;i++)
    {
        if(chr==referenceVector[i])
        {
            pos=i;
        }
    }
    return pos;
}

void Textbox::fillWithTexture(unsigned int position)
{   
    if(position>19)return;
    
    for(int i=0;i<15;i++)
         positionArray[i]=position;
}

void Textbox::updateTextRev(char* buffer,int len)
{
    bool unknown_char=0;
    int j=0;
    int i=0;
    while(i<15 && j<len)
    {  
    int pos=charIsUsable(buffer[j]);
        if(pos<0)
        {
            fillWithTexture(1);
            return;
        }
        positionArray[i]=pos;

        j++;
        i++;
    }

        while(i<15)
    {
        positionArray[i]=0;
        i++;
    }
};

void Textbox::updateText(char* buffer,int len)
{
    bool unknown_char=0;
    int n=len-1;
    int i=14;
    while(i>-1 && n>-1)
    {
        int pos=charIsUsable(buffer[n]);
        if(pos<0)
        {
            fillWithTexture(1);
            return;
        }
        positionArray[i]=pos;
        n--;
        i--;
    }
    while(i>-1)
    {
        positionArray[i]=0;
        i--;
    }
}

void Textbox::draw(VertexArray &arr,VertexBuffer &buff,IndexBuffer &ind,Shader &shader,Renderer &renderer,Window &window)
{
    for(int i=0;i<15;i++)
    {
    box[i].copyToBuffer(buff, window.getWidth(),window.getHeight());
    textures[positionArray[i]].bind();
    renderer.drawType1(arr,ind,shader);
    }
}