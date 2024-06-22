#ifndef PARTICLE_H
#define PARTICLE_H

#include </opt/homebrew/Cellar/sdl2/2.30.4/include/SDL2/SDL.h>

#define NUM_PARTICLES 1000
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 1000
#define TIME_STEP 0.01
#define PARTICLE_RADIUS 5
#define VELOCITY 100

typedef struct
{
    float x, y;
    float vx, vy;
} Particle;

void initialize_particles(Particle particles[], int num_particles);
void update_particles(Particle particles[], int num_particles, float dt);
SDL_Texture *create_particle_texture(SDL_Renderer *renderer, int radius, SDL_Color color);
void render_particles(SDL_Renderer *renderer, SDL_Texture *particle_texture, Particle particles[], int num_particles);

#endif // PARTICLE_H
