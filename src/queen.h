#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "board.h"

class Queen : public Piece
{
public:
    Queen(Color color,
         std::string apos,
         Piece_type type,
         std::string unicode,
         Square *,
         Board &);

    bool is_move_valid(const Square &);
    void move(Square &);
    bool canAttack(const Square &);
};


#endif // QUEEN_H