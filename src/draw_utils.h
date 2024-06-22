#ifndef DRAW_UTILS_H
#define DRAW_UTILS_H

#include </opt/homebrew/Cellar/sdl2/2.30.4/include/SDL2/SDL.h>
#include <stdint.h>

// Draw an unfilled circle outline
void DrawCircleParticle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius, SDL_Color color);

#endif // DRAW_UTILS_H
