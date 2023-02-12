//  GlobalFunctions.h
//  OOP_Project
//  Created by Aiman Khan on 03/11/2017.
//  Copyright © 2017 Aiman Khan. All rights reserved.
//
#ifndef GlobalFunctions_h
#define GlobalFunctions_h
#pragma once
#include <stdlib.h>
#include <sstream>

///this header contains static functions that can be used directly with class scope
struct GlobalFunctions
{
    static int GetSCREEN_WIDTH() //returns the width of the screen
    {
        return 1024;
    }

    static int GetSCREEN_HEIGHT() //returns the height of the screen
    {
        return 768;
    }
    static std::string int_to_string(int number) //function to convert an integer to string
    {
        std::stringstream ss;
        ss << number;
        return ss.str();
    }

};
#endif /* GlobalFunctions_h */
