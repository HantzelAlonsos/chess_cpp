#include "pawn.h"

Pawn::Pawn(Color side,
           std::string apos,
           Piece_type type,
           std::string unicode,
           Square *square,
           Board &board)
    : Piece(side, apos, type, unicode, square, board)
{
    hasMoved = false;
}

bool Pawn::isMoveValid(const Square &target)
{
    // This is shit- Fix this.
    if (apos == target.apos)
    {
        return false;
    }
    // TODO enpassant
    // determine black or white, only applicable to pawns.
    int tableTurner = 1;
    if (this->color == Color::black)
    {
        tableTurner = -1;
    }

    // possible moves
    int rowDiff = this->square->row - target.row;
    int colDiff = this->square->column - target.column;

    if (abs(colDiff == 0) && (tableTurner * rowDiff == -1))
    {
        // Move
        if (target.piece == nullptr)
        {
            // empty
            return true;
        }
    }

    if (abs(colDiff == 0) && (tableTurner * rowDiff == -2 && !this->hasMoved))
    {
        if (board.scanBetweenPcsAlongCol(*this->square, target) && target.piece == nullptr)
        {
            return true;
        }
    }

    if (tableTurner * rowDiff == -1 && abs(colDiff) == 1)
    {
        // attack
        if (target.piece != nullptr ||
            (board.getEnPassantSquare() != nullptr && board.getEnPassantSquare()->apos == target.apos))
        {
            return true;
        }
    }

    return false;
}

void Pawn::move(Square &target)
{
    // delete target.piece;
    // This is moved to board.
    int tableTurner = 1;
    if (this->color == Color::black)
    {
        tableTurner = -1;
    }
    board.forceClearEnPassant = false;
    // possible moves
    int rowDiff = this->square->row - target.row;
    int colDiff = this->square->column - target.column;

    if (abs(tableTurner * rowDiff == -2))
    {
        // Set en passant
        std::string enPassantStr = target.column + std::to_string(target.row - tableTurner);
        board.setEnpassant(enPassantStr, target);
    }

    if (board.getEnPassantSquare() != nullptr)
    {
        if (board.getEnPassantSquare()->apos == target.apos)
        {
            // This should preferably be done by board
            // But I cant make it work that way.
            board.forceClearEnPassant = true;
            board.enPassantPcSquare->piece = nullptr;
            
            square->piece = nullptr;
            target.piece = this;

            // Update piece info. Implied this->
            square = &target;
            apos = target.apos;

            hasMoved = true;
            return;
        }
    }
    // Move target
    // This should be handled with std::move later on.
    square->piece = nullptr;
    target.piece = this;

    // Update piece info. Implied this->
    square = &target;
    apos = target.apos;

    hasMoved = true;
}

bool Pawn::canAttack(const Square &target)
{
    // TODO consider removing code duplication from isMoveValid.
    int tableTurner = 1;
    if (this->color == Color::white)
    {
        tableTurner = -1;
    }

    // possible moves
    int rowDiff = this->square->row - target.row;
    int colDiff = this->square->column - target.column;

    if (tableTurner * rowDiff == 1)
    {
        if (abs(colDiff) == 1)
        {
            return true;
        }
    }
    // special case for pawn opening Not applicable when attacking.
    return false;
}