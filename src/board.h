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

typedef enum class State{
    normalPlay, whiteCheck, whiteMate, blackCheck, blackMate
}State;

typedef enum class Turn{
    white, 
    black, 
    god
}Turn;

typedef struct TransactionS{
    std::string sourceApos;
    std::string targetApos;
    Piece* sourcePcPtr;
    Piece* targetPcPtr;
    bool isCastling = false;
    bool isEnpassant = false;
    bool isPromotion = false;
    bool stateOfMoveBeforeAtCreationOfTransaction;
}TransactionS;

typedef struct EnPassant
{
    Piece* pieceThatJumped2Square;
    std::string enPassantAttackSquareApos;
}EnPassant; // En passant ? passed peasant ?


class Board
{
public:
    Board();
    // No longer using this but keep it around.
    // Square &operator[](std::string request)
    // {
    //     return getSquare(request);
    // }

    void createBoard();
    void render(Color);

    // Helper functions:
    bool scanBetweenPcsAlongRow(const Square&, const Square&) const;
    bool scanBetweenPcsAlongCol(const Square&, const Square&) const;
    bool scanBetweenPcsDiagonal(const Square&, const Square&) const;
    bool isCastlingValid(const Square &, const Square&) const;
    void handleCastling(Square&, Square&);
    void handleEnPassant(Square&, Square&);
    Square& getSquare(std::string);
    const Square& getConstSquare(std::string) const;
    State stateOfBoard(); // Not const since isKingInMate not const

    // Transactional functions:
    void addTransactionToBuffer(const Square&, const Square&);
    void emptyBuffer();
    void restoreTransaction();
    bool process(Move);

    
    Square* getEnPassantSquare() const;
    void setEnpassant(std::string, Piece*);
    TransactionS transaction;
    EnPassant enPassant;
    bool isEnPassantPossible;
private:
    Square errorSquare;
    Square board[8][8];
    Square* enPassantSquare;
    Piece * enPassantPc;
    
    // Methods used to create board
    void createKings();
    void createQueens();
    void createBishops();
    void createKnights();
    void createRooks();
    void createPawns();

    void clearOldEnPassant();

    // Board status functions
    bool handlePromotion(Square&, Square&, Move&);

    // Helper functions
    std::string determineCastlingRook(const Square&, const Square&) const;
    Piece* findPiece(Piece_type, Color) const;
    bool isKingInMate(Color);
    bool isKingInCheck(Color) const;
    bool isKingInCheckOnSquare(Color color,   const Square &target) const;
    std::vector<Piece*> findPieces(Piece_type, Color) const;
    std::vector<Piece*> findPieces(Color&) const;
    void askUserForInput(Move&); // Not in use

};


#endif // BOARD_H