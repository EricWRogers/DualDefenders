#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include <string>

#include "Debug.hpp"

namespace Canis
{
    enum WindowFlags
    {
        INVISIBLE = 0x1,
        FULLSCREEN = 0x2,
        BORDERLESS = 0x4
    };

    class Window
    {
    public:
        Window();
        ~Window();

        int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
        void setWindowName(std::string windowName);

        void swapBuffer();

        int getScreenWidth() { return _screenWidth; }
        int getScreenHeight() { return _screenHeight; }

    private:
        SDL_Window *_sdlWindow;
        int _screenWidth, _screenHeight;
    };
} // end of Canis namespace