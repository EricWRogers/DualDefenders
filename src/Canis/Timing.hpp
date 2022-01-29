#pragma once
#include <SDL.h>

namespace Canis
{
    class FpsLimiter
    {
    private:
        float _fps;
        float _maxFPS;
        float _frameTime;

        unsigned int _startTicks;

    public:
        FpsLimiter();
        ~FpsLimiter();

        void init(float targetFPS);
        void setTargetFPS(float targetFPS);
        void begin();
        void calculateFPS();

        float end();
    };
} // end of Canis namespace