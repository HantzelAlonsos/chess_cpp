#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "board.h"

class Rook : public Piece
{
public:
    Rook(Color color,
           std::string apos,
           Piece_type type,
           std::string unicode,
           Square *,
           Board &);

    ~Rook() = default;

    bool hasMoved;
    bool isMoveValid(const Square &);
    void move(Square &);
    bool canAttack(const Square &);

};

#endif // ROOK_H