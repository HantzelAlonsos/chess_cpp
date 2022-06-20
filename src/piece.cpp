#include "piece.h"
#include "board.h"

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
    
    board.isEnPassantPossible = false; // The ONLY time this should trigger
    // is when the pawn is jumps 2 steps. ALL other cases this is set to false

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