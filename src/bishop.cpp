#include "bishop.h"

Bishop::Bishop(Color color,
               std::string apos,
               Piece_type type,
               std::string unicode,
               Square *square,
               Board &board)
    : Piece(color, apos, type, unicode, square, board)
{
}

bool Bishop::isMoveValid(const Square &target)
{
if(apos == target.apos){
return false;
}
    // TODO
    int rowDiff = this->square->row - target.row;
    int colDiff = this->square->colInt - target.colInt;
    if( abs(rowDiff)-abs(colDiff) ==  0)
    {
        return board.scanBetweenPcsDiagonal(*this->square, target);
    }

    return false;
}

void Bishop::move(Square &target)
{
    // Nothing fancy.
    Piece::move(target);
}

bool Bishop::canAttack(const Square &target)
{
    // Nothing fancy.
    return Bishop::isMoveValid(target);
}