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

    EquationHandler eq(500);
    eq.setEquation((char*)("21*x^2+23*x+11=7"));
    std::cout<<eq.getCoeficientOf(0)<<'\n';
    std::cout<<eq.getCoeficientOf(1)<<'\n';
    std::cout<<eq.getCoeficientOf(2)<<'\n';

    return 0;
 
}
