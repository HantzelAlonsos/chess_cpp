#include "queen.h"

Queen::Queen(Color color,
             std::string apos,
             Piece_type type,
             std::string unicode,
             Square *square,
              Board &board)
    : Piece(color, apos, type, unicode, square, board)
{
}

bool Queen::isMoveValid(const Square &target)
{
    if (apos == target.apos)
    {
        return false;
    }

    int rowDiff = this->square->row - target.row;
    int colDiff = this->square->colInt - target.colInt;

    // She can move either diagonally or horizontally/veritacally.
    if (abs(rowDiff) - abs(colDiff) == 0)
    {
        return board.scanBetweenPcsDiagonal(*this->square, target);
    }
    else if (colDiff == 0 && rowDiff != 0)
    {
        return board.scanBetweenPcsAlongCol(*(this->square), target);
    }
    else if (rowDiff == 0 && colDiff != 0)
    {
        return board.scanBetweenPcsAlongRow(*(this->square), target);
    }

    return false;
}

void Queen::move(Square &target)
{
    // Nothing fancy.
    Piece::move(target);
}

bool Queen::canAttack(const Square &target)
{
    // Nothing fancy.
    return Queen::isMoveValid(target);
}
