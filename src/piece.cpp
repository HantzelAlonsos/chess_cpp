#include "piece.h"

Piece::Piece(Color color,
             std::string apos,
             Piece_type type,
             std::string unicode,
             Square *square,
             Board &board)

    : color(color), apos(apos), type(type),
      unicode(unicode), square(square), board(board)
{
}

bool Piece::isMoveValid(const Square &target)
{
    return false; //Should not call virtual function. Something is wrong
}

void Piece::move(Square &target)
{
    // This should be handled with std::move later on.
    (*square).piece = nullptr;
    target.piece = this;

    // Update piece info. Implied this->
    square = &target;
    apos = target.apos;
}

bool Piece::canAttack(const Square &target)
{
    return false; // ?
}