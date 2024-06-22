#include </opt/homebrew/Cellar/sdl2/2.30.4/include/SDL2/SDL.h>
#include "draw_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PARTICLES 10000
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 1000
#define TIME_STEP 0.01
#define PARTICLE_RADIUS 2

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
}

void render_particles(SDL_Renderer *renderer, Particle particles[], int num_particles)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < num_particles; i++)
    {
        DrawCircle(renderer, (int)particles[i].x, (int)particles[i].y, PARTICLE_RADIUS);
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

        render_particles(renderer, particles, NUM_PARTICLES);

        SDL_RenderPresent(renderer);

        SDL_Delay((int)(TIME_STEP * 1000)); // Delay to simulate time step
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
