#ifndef GHOST_H
#define GHOST_H
#include "GameObject.h"
#include "Level.h"

class Ghost : public GameObject
{
    public:
        Ghost(LTexture*, int,int);
        virtual ~Ghost();
        void Render(long int& frame, SDL_Renderer* gRenderer); //renders the moving clips of the ghosts
        void Scared_Render(long int&, SDL_Renderer*); //renders the scared clips of the ghosts
        void Move(Level*); //moves in a level grid
        virtual void ResetGhost() = 0; //resets the ghosts to the initial settings
        void setDirection(int);
        void setScaredGhost(bool set) {scared_ghost = set;}
        bool getScaredGhost() {return scared_ghost;}
        void ResetScaredFrame(){scared_frame = 0;} //resets the scared frame to zero.

    protected:
        SDL_Rect spriteClips[4]; //moving clips
        SDL_Rect spriteClips_scared[2]; //scared ghost clips
        SDL_Rect eyes; //clip for ghost eyes
        long int current_frame = 0; //to control moving ghost clips
        long int scared_frame = 0; //to control scared ghost clips
        int direction; //specifies where the ghosts have to move
        SDL_Rect currentCell; //specifies the current grid location of the ghost (rendered with blue)
        bool scared_ghost = false; //yo keep check whether sacred or non-scared ghosts is rendered on the screen
};

#endif // GHOST_H
