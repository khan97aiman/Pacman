#ifndef INKY_H
#define INKY_H

#include "Ghost.h"


class Inky : public Ghost
{
    public:
        Inky(LTexture*, int,int);
        virtual ~Inky();
        void ResetGhost(); //used to reset the ghosts to the initial settings
};

#endif // INKY_H
