#ifndef CLYDE_H
#define CLYDE_H

#include "Ghost.h"


class Clyde : public Ghost
{
    public:
        Clyde(LTexture*, int,int);
        virtual ~Clyde();
        void ResetGhost(); //to reset the ghost to initial settings
};

#endif // CLYDE_H
