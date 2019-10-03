/*
 * =====================================================================================
 *
 *       Filename:  Timer.hpp
 *
 *        Created:  02.10.2019 15:56:58
 *         Author:  Daniel Zawłocki
 *
 * =====================================================================================
 */
#pragma once

#include <SDL2/SDL.h>


class Timer {
    public:
        Timer();

        void start();
        void stop();
        void pause();
        void unpause();

        Uint32 getTicks();
        bool isStarted();
        bool isPaused();

    private:
        Uint32 startTicks;
        Uint32 pausedTicks;

        bool paused;
        bool started;
};
