#include "knight.h"

Knight::Knight(Color color,
               std::string apos,
               Piece_type type,
               std::string unicode,
               Square *square,
               Board &board)
    : Piece(color, apos, type, unicode, square, board)
{
}

bool Knight::isMoveValid(const Square &target)
{
    if (apos == target.apos)
    {
        return false;
    }
    // TODO
    int rowDiff = this->square->row - target.row;
    int colDiff = this->square->column - target.column;

    if (abs(colDiff) == 1 && abs(rowDiff) == 2 || abs(rowDiff) == 1 && abs(colDiff) == 2)
    {
        return true;
    }
    return false;
}

void Knight::move(Square &target)
{
    // Nothing fancy.
    Piece::move(target);
}

bool Knight::canAttack(const Square &target)
{
    // Nothing fancy.
    return Knight::isMoveValid(target);
}