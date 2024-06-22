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

    // FPS calculation variables
    Uint32 frameStart;
    int frameCount = 0;
    float fps = 0;
    Uint32 lastFpsCalculation = SDL_GetTicks();

    int quit = 0;
    SDL_Event e;
    while (!quit)
    {
        frameStart = SDL_GetTicks();

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

        // Calculate FPS
        frameCount++;
        if (SDL_GetTicks() - lastFpsCalculation >= 1000)
        { // Update every second
            fps = frameCount;
            printf("FPS: %.2f\n", fps);
            frameCount = 0;
            lastFpsCalculation = SDL_GetTicks();
        }

        // No delay, render as fast as possible
    }

    SDL_DestroyTexture(particle_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
