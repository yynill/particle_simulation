#include </opt/homebrew/Cellar/sdl2/2.30.4/include/SDL2/SDL.h>
#include "particle.h"
#include <stdio.h>

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
