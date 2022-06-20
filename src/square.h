#ifndef SQUARE_H
#define SQUARE_H

#include <string>

class Piece;

class Square
{
public:
    std::string apos;
    int pos;
    int row;
    int colInt;
    char column;
    Piece *piece;
};

#endif // SQUARE_H