#include "particle.h"
#include "draw_utils.h"
#include <stdlib.h>
#include <time.h>

void initialize_particles(Particle particles[], int num_particles)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < num_particles; i++)
    {
        particles[i].x = rand() % WINDOW_WIDTH;
        particles[i].y = rand() % WINDOW_HEIGHT;
        particles[i].vx = (rand() % 100) / 50.0f - 1.0f;
        particles[i].vy = (rand() % 100) / 50.0f - 1.0f;
    }
}

void update_particles(Particle particles[], int num_particles, float dt)
{
    for (int i = 0; i < num_particles; ++i)
    {
        particles[i].x += VELOCITY * particles[i].vx * dt;
        particles[i].y += VELOCITY * particles[i].vy * dt;

        if (particles[i].x < 0 || particles[i].x > WINDOW_WIDTH)
            particles[i].vx *= -1;
        if (particles[i].y < 0 || particles[i].y > WINDOW_HEIGHT)
            particles[i].vy *= -1;
    }
}

SDL_Texture *create_particle_texture(SDL_Renderer *renderer, int radius, SDL_Color color)
{
    int diameter = 2 * radius;
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, diameter, diameter);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Set transparent background
    SDL_RenderClear(renderer);
    DrawCircleParticle(renderer, radius, radius, radius, color);
    SDL_SetRenderTarget(renderer, NULL);
    return texture;
}

void render_particles(SDL_Renderer *renderer, SDL_Texture *particle_texture, Particle particles[], int num_particles)
{
    int diameter = 2 * PARTICLE_RADIUS;
    for (int i = 0; i < num_particles; i++)
    {
        SDL_Rect dst_rect = {(int)particles[i].x - PARTICLE_RADIUS, (int)particles[i].y - PARTICLE_RADIUS, diameter, diameter};
        SDL_RenderCopy(renderer, particle_texture, NULL, &dst_rect);
    }
}
