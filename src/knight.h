#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "board.h"

class Knight : public Piece
{
public:
    Knight(Color color,
         std::string apos,
         Piece_type type,
         std::string unicode,
         Square *,
         Board &);

    bool isMoveValid(const Square &);
    void move(Square &);
    bool canAttack(const Square &);
};

#endif // KNIGHT_H