#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "board.h"

// Pawn also requires to know what square it is standing on. As such
class Pawn : public Piece
{
public:
    Pawn(Color color,
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

#endif // PAWN_H