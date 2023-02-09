#include <Engine/WindowManager.hpp>

#include <stdexcept>

void WindowManager::init()
{
    /**
     * Main window is defined with a series of flags.
     *  - I haven't set some _FOCUS and _GRABBED flags because they suck...
     *  - I want the window in fullscreen and non-resizable for now
     *
     * TODO: Look further into Info.plist files and how to set the fields.
     *       https://wiki.libsdl.org/SDL2/SDL_WindowFlags
     */
    SDL_ClearError();
    window = SDL_CreateWindow(windowTitle.c_str(),
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              windowWidth,
                              windowHeight,
                              SDL_WINDOW_FULLSCREEN_DESKTOP |
                                  SDL_WINDOW_OPENGL |
                                  SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        string errorMessage = "SDL_CreateWindow: ";
        errorMessage += SDL_GetError();
        throw runtime_error(errorMessage);
    }

    /**
     * Renderer will not have any additional flags and by default uses any
     * hardware acceleration that is actively available. This can be explored
     * later in the future if there are any issues.
     */
    SDL_ClearError();
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
        string errorMessage = "SDL_CreateRenderer: ";
        errorMessage += SDL_GetError();
        throw runtime_error(errorMessage);
    }
}

void WindowManager::quit()
{
    // Destroy renderer
    SDL_ClearError();
    SDL_DestroyRenderer(renderer);
    if (SDL_GetError() == NULL)
    {
        cerr << SDL_GetError() << endl;
    }

    // Destroy window
    SDL_ClearError();
    SDL_DestroyWindow(window);
    if (SDL_GetError() == NULL)
    {
        cerr << SDL_GetError() << endl;
    }
}