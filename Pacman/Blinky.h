#ifndef BLINKY_H
#define BLINKY_H

#include "Ghost.h"


class Blinky : public Ghost
{
    public:
        Blinky(LTexture*, int,int);
        virtual ~Blinky();
        void ResetGhost(); //reset the ghost to the initial settings
};

#endif // BLINKY_H
