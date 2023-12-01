#include "../../MyEngine/math_engine/PSBmath.h"
#include "../../MyEngine/graphic_engine/buffers/buffers.h"
#include "../../MyEngine/graphic_engine/transformations/transformations.h"
#include "../../MyEngine/graphic_engine/textures/texture.h"
#include "../../MyEngine/graphic_engine/renderer/renderer.h"
#include "../../MyEngine/graphic_engine/windows/window.h"
#include "font.h"
#include "rectangle.h"

class Textbox
{
public:
Textbox(std::string texturePaths[20],Math::vec2f position,float width);
~Textbox();
void fillWithTexture(unsigned int position);
void draw(VertexArray &arr,VertexBuffer &buff,IndexBuffer &ind,Shader &shader,Renderer &renderer,Window &window);
void updateText(char *buffer,int len);
void updateTextRev(char *buffer,int len);
int charIsUsable(char chr);
private:
const char referenceVector[21]= " #^+-*/.()1234567890";
Texture textures[20];
int positionArray[15];
Character box[15];
};