#include "../MyEngine/graphic_engine/PSBgraphics.h"
#include "../MyEngine/graphic_engine/buffers/buffers.h"
#include "../MyEngine/graphic_engine/colors/color.h"
#include "../MyEngine/graphic_engine/geometry/geometry.h"
#include "../MyEngine/graphic_engine/geometry/geometry2.h"
#include "../MyEngine/graphic_engine/renderer/renderer.h"
#include "../MyEngine/graphic_engine/shaders/Shader.h"

#include "../MyEngine/graphic_engine/textures/texture.h"
#include "../MyEngine/graphic_engine/windows/window.h"
#include "../MyEngine/math_engine/PSBmath.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_haptic.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "ui_elements/font.h"
#include "ui_elements/button.h"
#include "ui_elements/rectangle.h"
#include "ui_elements/textbox.h"

#include "functionality/calculator.h"



int main()
{
//" #^+-*/.()1234567890"
std::string path_to_char[20]=
{
"fontBlack/space.png",
"fontBlack/sqrt.png",
"fontBlack/pow.png",
"fontBlack/plus.png",
"fontBlack/minus.png",
"fontBlack/mul.png",
"fontBlack/div.png",
"fontBlack/dot.png",
"fontBlack/par_left.png",
"fontBlack/par_right.png",
"fontBlack/one.png",
"fontBlack/two.png",
"fontBlack/three.png",
"fontBlack/four.png",
"fontBlack/five.png",
"fontBlack/six.png",
"fontBlack/seven.png",
"fontBlack/eight.png",
"fontBlack/nine.png",
"fontBlack/zero.png",
};


Window window("My Window",1000,1200);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glEnable(GL_BLEND);
SDL_Event event;
Renderer renderer;

char buffer[500];
strcpy(buffer,"");
int xMouse=0,yMouse=0;

Calculator calculator(500);

float offset=80.0f;

unsigned int indexData[6]=
{
0,2,1,
2,3,1
};

graphicalAtribute *ColAtributes=ColAtrib();
Shader *colShader=ColShader();
graphicalAtribute *texAtributes=TexAtrib();
Shader *texShader=TexShader();

VertexArray buttonArr((7*sizeof(float)));
buttonArr.bind();
VertexBuffer buttonBuffer(0,28*sizeof(float));
buttonArr.addData(buttonBuffer,ColAtributes,2);
colShader->bind();

Rectangle screen({500.0f,150.0f},900.0f,200.0f,{0.6157f,0.7255f,0.6824f,1.0f});
screen.copyToBuffer(buttonBuffer,1000.0f,1200);
                                                                                                
Button leftParButton({300.0f,300.0f+offset},390.0f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/par_left.png",'(');
Button rightParButton({700.0f,300.0f+offset},390.0f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/par_right.png",')');

Button clearButton({200.0f,450.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/clear.png",'c');
Button sqrtButton({400.0f,450.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/sqrt.png",'#');
Button powButton({600.0f,450.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/pow.png",'^');
Button divButton({800.0f,450.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/div.png",'/');

Button oneButton({200.0f,600.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/one.png",'1');
Button twoButton({400.0f,600.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/two.png",'2');
Button threeButton({600.0f,600.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/three.png",'3');
Button plusButton({800.0f,600.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/plus.png",'+');

Button fourButton({200.0f,750.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/four.png",'4');
Button fiveButton({400.0f,750.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/five.png",'5');
Button sixButton({600.0f,750.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/six.png",'6');
Button minusButton({800.0f,750.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/minus.png",'-');

Button sevenButton({200.0f,900.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/seven.png",'7');
Button eightButton({400.0f,900.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/eight.png",'8');
Button nineButton({600.0f,900.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/nine.png",'9');
Button mulButton({800.0f,900.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/mul.png",'*');

Button dotButton({200.0f,1050.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/dot.png",'.');
Button zeroButton({400.0f,1050.0f+offset},187.5f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/zero.png",'0');
Button equalButton({700.0f,1050.0f+offset},390.0f,135.0f,{0.294,0.294f,0.294f,1.0f},"font/equal.png",'=');

Textbox textbox(path_to_char,{500.0f,150.0f},900.0f);

VertexArray FontArr((5*sizeof(float)));
FontArr.bind();
VertexBuffer fontBuffer(0,20*sizeof(float));
FontArr.addData(fontBuffer,texAtributes,2);
IndexBuffer ind(indexData,6);
texShader->bind();

//oneButton.intersects({200.0f,600.0f+offset});


glClearColor(0.355f,0.36f,0.406f,0.0f);

while(!window.isClosed())
{
    renderer.clear();
    window.pollEvents(event);

    if(event.type==SDL_MOUSEMOTION)
    {
    
        SDL_GetMouseState(&xMouse,&yMouse);
        leftParButton.intersects({float(xMouse),float(yMouse)});
        rightParButton.intersects({float(xMouse),float(yMouse)});
        
        clearButton.intersects({float(xMouse),float(yMouse)});
        sqrtButton.intersects({float(xMouse),float(yMouse)});
        powButton.intersects({float(xMouse),float(yMouse)});
        divButton.intersects({float(xMouse),float(yMouse)});

        oneButton.intersects({float(xMouse),float(yMouse)});
        twoButton.intersects({float(xMouse),float(yMouse)});
        threeButton.intersects({float(xMouse),float(yMouse)});
        plusButton.intersects({float(xMouse),float(yMouse)});
        
        fourButton.intersects({float(xMouse),float(yMouse)});
        fiveButton.intersects({float(xMouse),float(yMouse)});
        sixButton.intersects({float(xMouse),float(yMouse)});
        minusButton.intersects({float(xMouse),float(yMouse)});

        sevenButton.intersects({float(xMouse),float(yMouse)});
        eightButton.intersects({float(xMouse),float(yMouse)});
        nineButton.intersects({float(xMouse),float(yMouse)});
        mulButton.intersects({float(xMouse),float(yMouse)});
        
        dotButton.intersects({float(xMouse),float(yMouse)});
        zeroButton.intersects({float(xMouse),float(yMouse)});
        equalButton.intersects({float(xMouse),float(yMouse)});
    }
    if(event.type==SDL_MOUSEBUTTONDOWN)
    {
        if(event.button.button==SDL_BUTTON_LEFT)
        {   
            if(oneButton.isSelected())strcat(buffer,"1");
            if(twoButton.isSelected())strcat(buffer,"2");
            if(threeButton.isSelected())strcat(buffer,"3");
            if(fourButton.isSelected())strcat(buffer,"4");
            if(fiveButton.isSelected())strcat(buffer,"5");
            if(sixButton.isSelected())strcat(buffer,"6");
            if(sevenButton.isSelected())strcat(buffer,"7");
            if(eightButton.isSelected())strcat(buffer,"8");
            if(nineButton.isSelected())strcat(buffer,"9");
            if(zeroButton.isSelected())strcat(buffer,"0");

            if(plusButton.isSelected())strcat(buffer,"+");
            if(minusButton.isSelected())strcat(buffer,"-");
            if(mulButton.isSelected())strcat(buffer,"*");
            if(divButton.isSelected())strcat(buffer,"/");
            if(powButton.isSelected())strcat(buffer,"^");
            if(sqrtButton.isSelected())strcat(buffer,"#");

            if(dotButton.isSelected())strcat(buffer,".");

            if(leftParButton.isSelected())strcat(buffer,"(");
            if(rightParButton.isSelected())strcat(buffer,")");

            if(clearButton.isSelected())strcpy(buffer,"");
            if(equalButton.isSelected())
            {   
                
                calculator.setExpr(buffer);
                calculator.evalExpr();
                if(calculator.getErrorMessage()!="")
                {
                    strcpy(buffer,calculator.getErrorMessage().c_str());
                }
                else
                {
                    char *temp=str_functions::double_to_string(calculator.getResult());
                    strcpy(buffer,temp);
                    delete [] temp;
            
                }
            }
            
            textbox.updateText(buffer,strlen(buffer));
        }
        
    }

    screen.copyToBuffer(buttonBuffer,window.getWidth(),window.getHeight());
    renderer.drawType1(buttonArr,ind,*colShader);

    leftParButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    leftParButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
    rightParButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    rightParButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());

    clearButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    clearButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
    sqrtButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    sqrtButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
    powButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    powButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
    divButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    divButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
   
    oneButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    oneButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
    twoButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    twoButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
    threeButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    threeButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
    plusButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    plusButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());

    fourButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    fourButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
    fiveButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    fiveButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
    sixButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    sixButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
    minusButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    minusButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());

    sevenButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    sevenButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
    eightButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    eightButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
    nineButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    nineButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
    mulButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    mulButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());

    dotButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    dotButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
    zeroButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    zeroButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
    equalButton.drawArea(*colShader,buttonArr,buttonBuffer,ind,renderer,window.getWidth(),window.getHeight());
    equalButton.drawFont(*texShader,FontArr,fontBuffer,ind,renderer,window.getWidth(),window.getHeight());
    
    textbox.draw(FontArr,fontBuffer,ind,*texShader,renderer,window);

    glViewport(0,0,window.getWidth(),window.getHeight());
    window.GLswap();
}

delete colShader;
delete texShader;

    return 0;
}
