#include <stdio.h>
#include <stdlib.h>

#include "../include/SDL2/SDL.h"


int main(int argc, char* argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    int quit = 0;
    int i;

    // Initialize SDL
    printf("SDL_Init()\n");
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Initialization failed: %s\n", SDL_GetError());

        return EXIT_FAILURE;
    }

    // Create an 800 x 600 window and an attached renderer
    printf("SDL_CreateWindowAndRenderer()\n");
    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

    if (window == NULL) {
        printf("Window creation failed: %s\n", SDL_GetError());

        return EXIT_FAILURE;
    }

    // Initialize random number generator
    srand(42);

    // Loop!
    while(!quit)
    {
        // Handle all queued events
        while (SDL_PollEvent(&event)) {
            // Handle event
            switch (event.type)
            {
            // SDL wants to quit!
            case SDL_QUIT:
                quit = 1;
                break;
            }
        }

        // Draw random pixels
        for(i = 0; i < 1000; i++)
        {
            SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, rand() % 256);
            SDL_RenderDrawPoint(renderer, rand() % 800, rand() % 600);
        }

        SDL_RenderPresent(renderer);
    }

    // Destroy the window
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}
