#ifndef KING_H
#define KING_H

#include "piece.h"
#include "board.h"

class King : public Piece
{
public:
    King(Color color,
         std::string apos,
         Piece_type type,
         std::string unicode,
         Square *,
         Board &);

    bool hasMoved;
    bool is_move_valid(const Square &);
    void move(Square &);
    bool canAttack(const Square &);
};



#endif // KING_H