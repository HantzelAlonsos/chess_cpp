#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"
#include "board.h"

class Bishop : public Piece
{
public:
    Bishop(Color color,
         std::string apos,
         Piece_type type,
         std::string unicode,
         Square *,
         Board &);

    ~Bishop() = default;

    bool isMoveValid(const Square &);
    void move(Square &);
    bool canAttack(const Square &);
};


#endif // BISHOP_H