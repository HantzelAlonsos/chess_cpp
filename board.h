#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <exception>
#include <stdexcept>
#include <cmath>


#include "square.h"
// Consider implementing a "pieces.h" which has includes to all pieces.
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pgnParser.h"

class Board
{
public:
    Board();
    Square &operator[](std::string request)
    {
        return getSquare(request);
    }

    void createBoard();
    Square& getSquare(std::string);
    const Square& getConstSquare(std::string) const;
    void render(Color);

    bool move(Move);
    bool isKingInCheck(Color) const;
    bool isKingInCheckOnSquare(Color color,   const Square &target) const;
    Piece* findPiece(Piece_type, Color) const;
    std::vector<Piece*> findPieces(Piece_type, Color) const;
    std::vector<Piece*> findPieces(Color&) const;
    // const or the "dont fuck around during these functions."
    bool scanBetweenPcsAlongRow(const Square&, const Square&) const;
    bool scanBetweenPcsAlongCol(const Square&, const Square&) const;
    bool scanBetweenPcsDiagonal(const Square&, const Square&) const;
    void addTransactionToBuffer(const Square&, const Square&);
    bool isCastlingValid(const Square &, const Square&) const;
    void handleCastling(Square&, Square&);
    void emptyBuffer();
    void restoreTransaction();
    bool isKingInMate(Color);
    //std::vector<Piece*> findPieces(Piece_type); // DO NOT IMPLEMENT
    //void restoreBuffer();
    Square* getEnPassantSquare() const;
    void setEnpassant(std::string, Square&);
    Square* EnPassantPcSquare;
    bool forceClearEnPassant;
private:
    Square board[8][8];
    std::string sourceApos;
    std::string targetApos;
    Piece* sourcePcPtr;
    Piece* targetPcPtr;
    Square* enPassantSquare;
    Piece * enPassantPc;
    bool enPassantSetThisTurn;
    bool handlePromotion(Square&, Move&);
    bool stateOfHasMovedOnTransaction;

    void createKings();
    void createQueens();
    void createBishops();
    void createKnights();
    void createRooks();
    void createPawns();

    void clearOldEnPassant();

    std::string determineCastlingRook(const Square&, const Square&) const;

};

#endif // BOARD_H