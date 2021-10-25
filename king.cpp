#include "king.h"

King::King(Color color,
           std::string apos,
           Piece_type type,
           std::string unicode,
           Square *square,
           Board &board)
    : Piece(color, apos, type, unicode, square, board)
{
}

bool King::is_move_valid(const Square &target)
{
    if (apos == target.apos)
    {
        return false;
    }

    int rowDiff = this->square->row - target.row;
    int colDiff = this->square->colInt - target.colInt;

    if (abs(rowDiff) == 1 && colDiff == 0 || abs(colDiff) == 1 && rowDiff == 0 || (abs(rowDiff) == 1 && abs(colDiff) == 1))
    {
        return true;
    }
    if (abs(rowDiff) == 0 && (abs(colDiff) == 2))
    {
        // Castling!
        return board.isCastlingValid(*this->square, target);
    }
    return false;
}

void King::move(Square &target)
{
    // Nothing fancy.
    hasMoved= true;
    Piece::move(target);
}

bool King::canAttack(const Square &target)
{
    // Nothing fancy.
    return King::is_move_valid(target);
}
