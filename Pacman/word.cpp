#include "word.h"

using namespace std;

Word::Word()
{
    width=height=0;
    text="\0";
    wordLen=0;
    chars=NULL;
}

Word::Word(string text, LTexture* image, float x, float y)
{
    this->spriteSheetTexture = image;
    width = 0;
    height = 40;
    wordLen = text.size();
    this->text = text;
    chars = new Character[wordLen]; //create a dynamic array of characters
    position.x = x;
    position.y = y;
    float posX = position.x-16*(wordLen-1);
    for(int i=0; i<wordLen; i++)
    {
        chars[i] = Character(spriteSheetTexture,posX+width,position.y, (int)text[i]); //make charaters and store that in dynamic array
        width += 32;
    }
}
void Word::Render(SDL_Renderer* gRenderer)
{
    for(int i=0; i<wordLen; i++)
    {
        chars[i].Render(gRenderer,false);
    }
}

int Word::getLength()
{
    return wordLen;
}

Word::~Word()
{
    cout << "Word " << text << " is destroyed" << endl;
    if (chars!=NULL)
    {
        delete[] chars; //deallocating dynamic array
        chars = NULL;
    }

}

int Word::getWidth()
{
    return width;
}

void Word::changeWord(std::string text)
{
    this->text = text;
    width = 0;
    height = 40;
    wordLen = text.size();
    delete chars; //to deallocate the previous character array
    chars = new Character[wordLen]; //create new now
    float posX = position.x-16*(wordLen-1);
    for(int i=0; i<wordLen; i++)
    {
        chars[i] = Character(spriteSheetTexture,posX+width,position.y, (int)text[i]); //make charaters and store that in dynamic array
        width += 32;
    }
}
void Word::operator = (const Word& cpy)
{
    this->position.x = cpy.position.x;
    this->position.y = cpy.position.y;
    this->spriteSheetTexture = cpy.spriteSheetTexture;
    this->text = cpy.text;
    this->wordLen = cpy.wordLen;
    delete chars; //delete previous character array
    chars = new Character[wordLen]; //make new
    for(int i = 0;i<wordLen;i++)
    {
        chars[i] = cpy.chars[i];
    }
    this->width = cpy.width;
    this->height = cpy.height;
}

