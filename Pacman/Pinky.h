#ifndef PINKY_H
#define PINKY_H

#include "Ghost.h"


class Pinky : public Ghost
{
    public:
        Pinky(LTexture*, int,int);
        virtual ~Pinky();
        void ResetGhost(); //used to reset the ghosts to the initial settings
};

#endif // PINKY_H
