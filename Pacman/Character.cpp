#include"Character.h"
#include<iostream>
Character::Character()
{

}

Character::Character(LTexture* image, float x, float y, int ascii)
{
    spriteSheetTexture = image;
    spriteClips.w = 42;
    spriteClips.h = 28;

    int diff=0;

    ///selects the Character image according to its ascii value
    if(ascii==32)
    {
        spriteClips.x=168;
        spriteClips.y=256;
        spriteClips.w=10;
    }
    else if(ascii==33)
    {
        spriteClips.x=294;
        spriteClips.y=224;
    }
    else if(ascii>=48 && ascii<=57)
    {
        character_value=48;
        spriteClips.x = 168;
        spriteClips.y = 192;

        diff=ascii-character_value;
        if (diff>3)
        {
            spriteClips.x = 0;
            spriteClips.y +=33;
            character_value+=4;
            diff=ascii-character_value;
        }
        spriteClips.x+=42*diff;
    }
    else if(ascii==63)
    {
        spriteClips.x=252;
        spriteClips.y=224;
    }
    else if((ascii>=65 && ascii<=90) || (ascii>=97 && ascii<=122))
    {
        if((ascii>=97) && (ascii<=122))
            ascii-=32;
        character_value = 65;
        spriteClips.x = 0;
        spriteClips.y = 0;
        diff=ascii-character_value;
        spriteClips.y +=32*(diff/8);
        character_value+=8*(diff/8);
        diff=ascii-character_value;
        spriteClips.x+=42*diff;
    }

    character_value=ascii;

    position.x = x;
    position.y = y;

    this->width = spriteClips.w;
    this->height = spriteClips.h;
}

Character::~Character()
{
    /*char n = character_value + 97;
    std::cout<<"\nCharacter "<<n<<" Destroyed";*/
}

void Character::Render( SDL_Renderer* gRenderer, bool debug)
{

    spriteSheetTexture->RenderTexture( position.x - width/2, position.y - height/2, gRenderer, &spriteClips);
    if(debug == true)
    {
        SDL_Rect rect = { position.x - width/2, position.y - height/2, width, height };
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
        SDL_RenderDrawRect( gRenderer, &rect );
    }
}

void Character::operator = (const Character& cpy)
{
    this->position=cpy.position;
    this->spriteClips=cpy.spriteClips;

    this->spriteSheetTexture=cpy.spriteSheetTexture;
    this->character_value=cpy.character_value;
    this->width=cpy.width;
    this->height=cpy.height;
}
