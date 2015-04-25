#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "../include/SDL2/SDL.h"


int main(int argc, char* argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    int quit = 0;
    int i;


    printf("Starting...\n");
    fflush(stdout);


    sleep(1);


    // Initialize SDL
    printf("SDL_Init()\n");
    fflush(stdout);
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Initialization failed: %s\n", SDL_GetError());
        fflush(stdout);

        return EXIT_FAILURE;
    }


    sleep(1);


    SDL_DisplayMode mode;
    printf("SDL_GetCurrentDisplayMode()\n");
    fflush(stdout);
    if(SDL_GetCurrentDisplayMode(0, &mode) != 0)
    {
        printf("Could not get current mode: %s\n", SDL_GetError());
        fflush(stdout);

        return EXIT_FAILURE;
    }

    int screenWidth = mode.w;
    int screenHeight = mode.h;

    // Create an 800 x 600 window and an attached renderer
    printf("SDL_CreateWindowAndRenderer(%i, %i)\n",
           screenWidth,
           screenHeight);
    fflush(stdout);
    SDL_CreateWindowAndRenderer(screenWidth, screenHeight, 0, &window, &renderer);

    if (window == NULL) {
        printf("Window creation failed: %s\n", SDL_GetError());
        fflush(stdout);

        return EXIT_FAILURE;
    }


    printf("Initialized, drawing...\n");
    fflush(stdout);


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
        for(i = 0; i < 5000; i++)
        {
            SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, rand() % 256);
            SDL_RenderDrawPoint(renderer, rand() % screenWidth, rand() % screenHeight);
        }

        SDL_RenderPresent(renderer);
    }

    // Destroy the window
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

    return EXIT_SUCCESS;
}
