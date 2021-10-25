#include "rook.h"

Rook::Rook(Color color,
           std::string apos,
           Piece_type type,
           std::string unicode,
           Square *square,
           Board &board)
    : Piece(color, apos, type, unicode, square, board)
{
    hasMoved = false;
}

bool Rook::is_move_valid(const Square &target)
{
    if (apos == target.apos)
    {
        return false;
    }
    // TODO rook, technically a king move.
    int rowDiff = this->square->row - target.row;
    int colDiff = this->square->colInt - target.colInt;
    if (colDiff != 0 && rowDiff != 0)
    {
        // Can move in either column or row. Not both.
        return false;
    }
    if (colDiff != 0)
    {
        return board.scanBetweenPcsAlongRow(*(this->square), target);
    }
    else
    {
        return board.scanBetweenPcsAlongCol(*(this->square), target);
    }
    return false;
}

void Rook::move(Square &target)
{
    // Nothing fancy.
    hasMoved = true;
    Piece::move(target);
}

bool Rook::canAttack(const Square &target)
{
    // Nothing fancy.
    return Rook::is_move_valid(target);
}