#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "board.h"

class Pawn : public Piece
{
public:
    Pawn(Color color,
         std::string apos,
         Piece_type type,
         std::string unicode,
         Square *,
         Board &);
    
    ~Pawn() = default; // Why should this be virtual ? :S

    bool hasMoved;
    bool isMoveValid(const Square &);
    void move(Square &);
    bool canAttack(const Square &);
};

#endif // PAWN_H