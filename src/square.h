#ifndef SQUARE_H
#define SQUARE_H

#include <string>

class Piece;

class Square
{
public:
    std::string apos; // algebraic position, a4, e4 etc
    //int pos; // Deprecated: use apos instead
    int row; // 1 indexed
    int colInt; // Columns are lettered in chess. 1 indexed
    char column; 
    Piece *piece;
};

#endif // SQUARE_H