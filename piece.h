#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>
#include "square.h"
#include <iostream>

// Forward decl 
class Board;

enum class Piece_type
{
    king,
    queen,
    bishop,
    knight,
    rook,
    pawn,
    none
};

enum class Color
{
    white,
    black // Do not implement third type.  This will 
    // break search functions.
};

class Piece
{
public:
    Color color;
    std::string apos;
    Piece_type type;
    std::string unicode;
    Square *square;
    Board &board;
    Piece(Color side,
          std::string apos,
          Piece_type type,
          std::string unicode,
          Square *square,
          Board &board);

    static Piece* bufferPtr;
    virtual bool is_move_valid(const Square &);
    virtual void move(Square &);
    virtual bool canAttack(const Square&);
};

#endif // PIECE_H