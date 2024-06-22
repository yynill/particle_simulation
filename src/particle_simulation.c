#include </opt/homebrew/Cellar/sdl2/2.30.4/include/SDL2/SDL.h>
#include "draw_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PARTICLES 10000
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 1000
#define TIME_STEP 0.01
#define PARTICLE_RADIUS 5
#define VELOCITY 200

typedef struct
{
    float x, y;
    float vx, vy;
} Particle;

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
        // Update position based on velocity and time step
        particles[i].x += VELOCITY * particles[i].vx * dt;
        particles[i].y += VELOCITY * particles[i].vy * dt;

        // Check and handle collisions with window boundaries
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
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    DrawCircle(renderer, radius, radius, radius, color);
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

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow("Particle Simulation", 100, 100, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == NULL)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(win);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Color particleColor = {3, 177, 255, 255};
    SDL_Texture *particle_texture = create_particle_texture(renderer, PARTICLE_RADIUS, particleColor);

    Particle particles[NUM_PARTICLES];
    initialize_particles(particles, NUM_PARTICLES);

    int quit = 0;
    SDL_Event e;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
        }

        update_particles(particles, NUM_PARTICLES, TIME_STEP);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        render_particles(renderer, particle_texture, particles, NUM_PARTICLES);

        SDL_RenderPresent(renderer);
        SDL_Delay((int)(TIME_STEP * 1000)); // Delay to simulate time step
    }

    SDL_DestroyTexture(particle_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
