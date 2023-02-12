#ifndef PACMAN_H
#define PACMAN_H
#include "GameObject.h"
#include "Level.h"
#include "Ghost.h"

class Pacman : public GameObject
{
    public:
        Pacman(LTexture*, int,int);
        virtual ~Pacman();
        void eat(Level*,Ghost**,Mix_Chunk*, Mix_Chunk*); //for eating candies and lollipops
        void setDirection(int); //sets the direction of the pacman according to the user input
        int getDirection();
        void Move(Level*); //for moving pacman in the grid
        void Render(long int& frame, SDL_Renderer* gRenderer);
        void ResetPacman(); //used to reset the pacman to the initial settings
        int getScore() {return score;}
        int getTargetScore() {return targetScore;}
        int getLives() {return lives;}
        bool CheckCollision(Ghost*); //checks collision with ghosts
        void setLives(int lives) {this->lives = lives;}
        void setScore(int score) {this->score = score;}
        void EatGhost(Ghost*); //used to eat blue or white (scared) ghosts
        void SetTargetScore(int);
        bool GetEndDeathAnimation() {return endDeathAnimation;} //tells whether or not pacman death animation has ended
        void setEndDeathAnimation(bool set) {endDeathAnimation = set;}

    private:
        SDL_Rect spriteClipsAlive[47]; //pacman moving clips
        SDL_Rect spriteClipsDead[23]; //pacman death clips
        int direction; //direction of moving
        double angle; //to change the rendering angle of the pacman according to the direction
        int target_x; //sets the target location of the grid on x axis
        int target_y; //sets the target location of the grid on y axis
        SDL_Rect currentCell; //specifies the current cell of the pacman (rendered with red on screen)
        SDL_Rect targetCell; //specifies the target cell of the pacman (rendered with yellow on screen)
        int score; //this score represents the total score of the game which inlcudes eating ghosts, candies and lollipops
        int targetScore = 0; //this score represents the number of lollipops and candies eaten. A player has to make this target score equal to the target score of the level in order to win
        int lives;
        int death_frame; //to keep check of what frame of pacman death is being rendered
        bool endDeathAnimation = false;
};

#endif // PACMAN_H
