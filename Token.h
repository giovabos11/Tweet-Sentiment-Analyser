//
// Created by giova on 2/4/2022.
//
#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include "DSString.h"

struct Token {
    DSString key;
    int positiveVal = 0;
    int negativeVal = 0;
};

#endif // TOKEN_H_INCLUDED
