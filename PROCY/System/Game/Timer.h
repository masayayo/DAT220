//
// Created by Masaya on 11/4/2017.
//

#ifndef PROCY_TIMER_H
#define PROCY_TIMER_H

#include <SFML/Graphics.hpp>

struct Timer {
        sf::Clock mC;
        float runTime;
        bool bPaused;

        Timer() {
                bPaused = false;
                runTime = 0;
                mC.restart();
        }

        void Reset() {
                mC.restart();
                runTime = 0;
                bPaused = false;
        }

        void Start() {
                if (bPaused) {
                        mC.restart();
                }
                bPaused = false;
        }

        void Pause() {
                if (!bPaused) {
                        runTime += mC.getElapsedTime().asSeconds();
                }
                bPaused = true;
        }

        float GetElapsedSeconds() {
                if (!bPaused) {
                        return runTime + mC.getElapsedTime().asSeconds();
                }
                return runTime;
        }
};

#endif //PROCY_TIMER_H
