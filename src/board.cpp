#include "board.h"

Board::Board()
{
    createBoard();
}

void Board::createBoard()
{

    int counter = 0;

    for (int row = 1; row <= 8; ++row)
    {
        char column = 'a';
        for (int col = 0; col <= 7; ++col)
        {
            // We start with row and colInt 1 to make since chess is not 0 indexed
            board[row - 1][col].row = row;
            board[row - 1][col].colInt = col + 1;
            board[row - 1][col].column = column;
            board[row - 1][col].apos = column + std::to_string(row);

            board[row - 1][col].piece = nullptr;
            column = static_cast<char>(column + 1);
            counter++;
        }
    }

    errorSquare.apos = NOT_APPLICABLE;
    errorSquare.piece = nullptr; // TODO const this ?
    createKings();
    createQueens();
    createBishops();
    createKnights();
    createRooks();
    createPawns();
}

Square &Board::getSquare(std::string request)
{

    for (auto &row : board)
    {
        for (auto &it : row)
        {
            if (it.apos == request)
            {
                return it;
            }
        }
    }
    return errorSquare;
}

const Square &Board::getConstSquare(std::string request) const
{

    for (auto &row : board)
    {
        for (auto &it : row)
        {
            if (it.apos == request)
            {
                return it;
            }
        }
    }
    return errorSquare;
}

State Board::stateOfBoard()
{
    if (isKingInCheck(Color::white))
    {
        if (isKingInMate(Color::white))
        {
            return State::whiteMate;
        }
        return State::whiteCheck;
    }
    else if (isKingInCheck(Color::black))
    {
        if (isKingInMate(Color::black))
        {
            return State::blackMate;
        }
        return State::blackCheck;
    }

    return State::normalPlay;
}

void Board::render(Color player)
{
    // TODO graphical? string is fine for now.
    // player color indicates pov direction.

    std::string accumulator = "\n";

    if (player == Color::black)
    {
        accumulator += "  h g f e d c b a \n";
        for (int row_c = 0; row_c <= 7; ++row_c)
        {
            accumulator += std::to_string(row_c + 1) + " ";
            for (int column_c = 7; column_c >= 0; --column_c)
            {
                if (board[row_c][column_c].piece != nullptr)
                {
                    accumulator += board[row_c][column_c].piece->unicode + " ";
                }
                else
                {
                    accumulator += "  ";
                }
            }
            accumulator += " " + std::to_string(row_c + 1);
            accumulator += "\n";
        }
        accumulator += "  h g f e d c b a \n";
    }
    else
    {
        accumulator += "  a b c d e f g h\n";
        for (int row_c = 7; row_c >= 0; --row_c)
        {
            accumulator += std::to_string(row_c + 1) + " ";
            for (int column_c = 0; column_c <= 7; ++column_c)
            {

                if (board[row_c][column_c].piece != nullptr)
                {
                    accumulator += board[row_c][column_c].piece->unicode + " ";
                }
                else
                {
                    accumulator += "  ";
                }
            }
            accumulator += " " + std::to_string(row_c + 1);
            accumulator += "\n";
        }
        accumulator += "  a b c d e f g h\n";
    }
    std::cout << accumulator << std::endl;
}

bool Board::process(Move move)
{

    Square &source = getSquare(move.source);
    Square &target = getSquare(move.target);

    if (source.piece == nullptr) // Cant move square with no piece.
    {
        return false;
    }

    if (target.piece != nullptr && target.piece->color == source.piece->color)
    {
        std::cout << "move encountered same color" << std::endl;
        return false;
    }

    addTransactionToBuffer(source, target);

    if (source.piece->isMoveValid(target))
    {
        if (transaction.isCastling)
        {
            handleCastling(source, target);
        }
        else if (transaction.isPromotion)
        {
            handlePromotion(source, target, move);
        }
        else if (transaction.isEnpassant)
        {
            handleEnPassant(source, target);
        }
        else
        {
            source.piece->move(target);
        }

        if (isKingInCheck(target.piece->color))
        {
            // selfcheck. Not allowed
            restoreTransaction();
            return false;
        }
    }
    else
    {
        return false;
    }

    emptyBuffer();

    // Check and check mate is actually not related to move.
    if (isKingInCheck(Color::black))
    {
        if (isKingInMate(Color::black))
        {
            std::cout << "Mate!" << std::endl;
            return true;
        }
        std::cout << "Black is in check" << std::endl;
    }
    if (isKingInCheck(Color::white))
    {
        if (isKingInMate(Color::white))
        {
            std::cout << "Mate!" << std::endl;
            return true;
        }
        std::cout << "White is in check" << std::endl;
    }

    return true;
}

bool Board::isKingInCheck(Color color) const
{
    Square &kingSquare = *(findPiece(Piece_type::king, color)->square);
    return isKingInCheckOnSquare(color, kingSquare);
}

bool Board::isKingInCheckOnSquare(Color color, const Square &target) const
{
    // When transitioning from
    Color searchedColorForEnemyPieces = Color::white;

    // This is disgusting. Fix this.
    if (color == Color::white)
    {
        searchedColorForEnemyPieces = Color::black;
    }
    std::vector<Piece *> enemyPieces = findPieces(searchedColorForEnemyPieces);

    for (auto ePiecePtr : enemyPieces)
    {
        if (ePiecePtr->canAttack(target))
        {
            return true;
        }
    }

    return false;
}

Piece *Board::findPiece(Piece_type searchedType, Color searchedColor) const
{
    for (auto &row : board)
    {
        for (auto &it : row)
        {
            if (it.piece != nullptr &&
                it.piece->type == searchedType &&
                it.piece->color == searchedColor)
            {
                return it.piece;
            }
        }
    }
    return nullptr;
}

std::vector<Piece *> Board::findPieces(Piece_type searchedType, Color searchedColor) const
{
    std::vector<Piece *> returnCollector;
    for (auto &row : board)
    {
        for (auto &it : row)
        {
            if (it.piece != nullptr &&
                it.piece->type == searchedType &&
                it.piece->color == searchedColor)
            {

                returnCollector.push_back(it.piece);
            }
        }
    }
    if (returnCollector.empty())
    {
        throw "The searched for term was not found";
    }
    return returnCollector;
}

std::vector<Piece *> Board::findPieces(Color &searchedColor) const
{
    // TODO fix code duplication.
    std::vector<Piece *> returnCollector;
    for (auto &row : board)
    {
        for (auto &it : row)
        {
            if (it.piece != nullptr &&
                it.piece->color == Color::white && searchedColor == Color::white)
            {
                returnCollector.push_back(it.piece);
            }
            else if (it.piece != nullptr &&
                     it.piece->color == Color::black && searchedColor == Color::black)
            {
                returnCollector.push_back(it.piece);
            }
        }
    }
    if (returnCollector.empty())
    {
        throw "The searched for term was not found";
    }
    return returnCollector;
}

bool Board::scanBetweenPcsAlongRow(const Square &source, const Square &target) const
{
    //  Source and target are obviously interchangable.
    //  Just to keep it inline with remaining code.

    // Rename this. ensureNoPiecesBetweenPcsRow() ?
    // returns true if nothing between you and where you want to go.
    if (source.row != target.row)
    {
        std::cout << "rows must align" << std::endl;
        throw;
    }
    int direction = ((source.colInt - target.colInt) < 0) ? 1 : -1;
    // This looks odd. array is 0 indexed and row is 1 indexed.
    // So we offset 1 to make row be indexed to array.
    // but then we add direction so as to not start on source square.
    // if we start on source square we will find it is occupied.
    // and therefor we cant move.
    // Consider refactoring such that index of array and squares is 0 and
    // apos is the only thing that is "chess indexed". TODO
    for (int i = source.colInt - 1 + direction; i != target.colInt - 1; i = i + direction)
    {
        if (board[source.row - 1][i].piece != nullptr)
        {
            return false;
        }
    }
    return true;
}

bool Board::scanBetweenPcsAlongCol(const Square &source, const Square &target) const
{
    //  Source and target are obviously interchangable.
    //  Just to keep it inline with remaining code.

    // Rename this. ensureNoPiecesBetweenPcsRow() ?
    // returns true if nothing between you and where you want to go.
    if (source.colInt != target.colInt)
    {
        std::cout << "source and target column do not match"
                  << source.column << "  " << target.column << std::endl;
        throw;
    }
    int direction = (source.row - target.row < 0) ? 1 : -1;
    // This looks odd. array is 0 indexed and colInt is 1 indexed.
    // So we offset 1 to make row be indexed to array.
    // but then we add direction so as to not start on source square.
    // if we start on source square we will find it is occupied.
    // and therefor we cant move.
    // Consider refactoring such that index of array and squares is 0 and
    // apos is the only thing that is "chess indexed". TODO
    for (int i = source.row - 1 + direction; i != target.row - 1; i += direction)
    {
        // std::cout << "along Column Scanning" << board[i][source.colInt - 1].apos << std::endl;
        if (board[i][source.colInt - 1].piece != nullptr)
        {
            return false;
        }
    }
    return true;
}

bool Board::scanBetweenPcsDiagonal(const Square &source, const Square &target) const
{
    // std::cout << "scan between: " << source.apos << " & " << target.apos << std::endl;
    double rowDiff = source.row - target.row;
    double colDiff = source.colInt - target.colInt;

    if (rowDiff == 0 && colDiff == 0)
    {
        return false;
    }

    if (abs(rowDiff) - abs(colDiff) != 0)
    {
        std::cout << source.apos << "  " << target.apos << std::endl;
        std::cout << abs(rowDiff / colDiff) << "  " << std::endl;
        throw;
    }
    // The direction is on both planes.
    int colDirection = (source.colInt - target.colInt < 0) ? 1 : -1;
    int rowDirection = (source.row - target.row < 0) ? 1 : -1;

    int j = source.row - 1 + rowDirection;
    // KISS
    int i = source.colInt - 1 + colDirection;
    while (i != target.colInt - 1 && j != target.row - 1)
    {
        // std::cout << "Diagonal Scanning" << board[j][i].apos << std::endl;
        if (board[j][i].piece != nullptr)
        {
            return false;
        }
        j += rowDirection;
        i += colDirection;
    }
    return true;
}

bool Board::isKingInMate(Color color)
{
    // Try move ALL pieces to ALL positions.
    // https://tenor.com/view/everyone-angry-gary-oldman-gif-13877652

    std::cout << "checking for mate" << std::endl;
    auto ourPieces = findPieces(color);
    bool skip = false;
    for (size_t i = 0; i < ourPieces.size(); i++)
    {
        Piece *pcPtr = ourPieces[i];

        for (auto &row : board)
        {
            for (auto &target : row)
            {
                skip = false;
                if (target.piece != nullptr)
                {
                    if (target.piece->color == color)
                    {
                        skip = true;
                    }
                }
                if (!skip)
                {
                    if (pcPtr->isMoveValid(target))
                    {
                        addTransactionToBuffer(*(pcPtr->square), target);
                        std::string storage = pcPtr->apos;

                        pcPtr->move(target);
                        if (!isKingInCheck(color))
                        {
                            std::cout << storage << " to " << target.apos << " will stop check mate" << std::endl;
                            restoreTransaction();
                            return false;
                        }
                        restoreTransaction();
                    }
                }
            }
        }
    }
    return true;
}

void Board::addTransactionToBuffer(const Square &source, const Square &target)
{
    transaction.sourceApos = source.apos;
    transaction.targetApos = target.apos;
    transaction.sourcePcPtr = source.piece;
    transaction.targetPcPtr = target.piece;
    transaction.isCastling = false;
    transaction.isEnpassant = false;
    transaction.isPromotion = false;

    if (transaction.sourcePcPtr->type == Piece_type::rook || transaction.sourcePcPtr->type == Piece_type::pawn || transaction.sourcePcPtr->type == Piece_type::king)
    {

        transaction.stateOfMoveBeforeAtCreationOfTransaction = static_cast<Rook *>(transaction.sourcePcPtr)->hasMoved;
    }
}

bool Board::isCastlingValid(const Square &source, const Square &target) const
{

    // Determine rook apos. This function might be called even if its not a castling move.

    std::string squareStr = determineCastlingRook(source, target);
    if (squareStr == "WRONG")
    {
        return false;
    }

    // nothing between pieces.
    const Square rookSquare = getConstSquare(squareStr);

    // Pieces have not moved.
    if (rookSquare.piece != nullptr)
    {
        Rook *rookPtr = (Rook *)rookSquare.piece;
        King *kingPtr = (King *)source.piece;
        if (rookPtr->hasMoved)
        {
            std::cout << "rook " << rookPtr->apos << " has moved and thefore you cannot castle" << std::endl;
            return false;
        }
        else if (kingPtr->hasMoved)
        {
            std::cout << "the king has moved and thefore you cannot castle" << std::endl;
            return false;
        }
    }
    else
    {
        return false;
    }

    if (!scanBetweenPcsAlongRow(source, rookSquare))
    {
        return false;
    }

    return true;
}

void Board::handleCastling(Square &source, Square &target)
{
    std::cout << "Handle castling" << std::endl;
    std::string squareStr = determineCastlingRook(source, target);
    Square &rookSource = getSquare(squareStr);
    std::string rookEndSquare;
    if (target.column == 'c')
    {
        rookEndSquare = "d" + std::to_string(target.row);
    }
    else if (target.column == 'g')
    {
        rookEndSquare = "f" + std::to_string(target.row);
    }
    else
    {
        throw std::out_of_range("The target of castling is not either c or f");
    }
    Square &rookTarget = getSquare(rookEndSquare);

    // move king
    source.piece->move(target);
    // move rook
    rookSource.piece->move(rookTarget);
}

void Board::setEnpassant(std::string attackSquareApos, Piece *pieceThatJumped2Squares)
{
    // Does not matter what was here before. This needs to be cleared.
    enPassant.enPassantAttackSquareApos = attackSquareApos;
    enPassant.pieceThatJumped2Square = pieceThatJumped2Squares;
    isEnPassantPossible = true;
}

void Board::handleEnPassant(Square &source, Square &target)
{
    transaction.targetPcPtr = enPassant.pieceThatJumped2Square;
    source.piece->move(target);
    getSquare(enPassant.pieceThatJumped2Square->apos).piece = nullptr;
}

void Board::emptyBuffer()
{
    delete transaction.targetPcPtr;
    if (transaction.isPromotion)
    {
        delete transaction.sourcePcPtr;
    }
}

void Board::restoreTransaction()
{
    // TODO implement std::move if unique.
    Square &target = getSquare(transaction.targetApos);
    target.piece = transaction.targetPcPtr;
    if (target.piece != nullptr)
    {
        target.piece->apos = transaction.targetApos;
        target.piece->square = &target;
    }

    // Source piece cannot be null
    Square &source = getSquare(transaction.sourceApos);
    source.piece = transaction.sourcePcPtr;
    source.piece->apos = transaction.sourceApos;
    source.piece->square = &source;

    if (transaction.sourcePcPtr->type == Piece_type::rook || transaction.sourcePcPtr->type == Piece_type::pawn || transaction.sourcePcPtr->type == Piece_type::king)
    {
        static_cast<Rook *>(transaction.sourcePcPtr)->hasMoved = transaction.stateOfMoveBeforeAtCreationOfTransaction;
    }
}

void askUserForInput(Move& move)
{
    std::string userInput;
    std::cout << userInput;
    while (userInput.size() != 1)
    {
        std::cout << "Please pick promotion piece: (q,b,r,n)" << std::endl;
        std::cin >> userInput;
    }
    std::cout << "userInput 0: " << userInput[0] << std::endl;
    switch (userInput[0])
    {
    case 'q':
        move.promotion = Promotion::Queen;
        break;
    case 'b':
        move.promotion = Promotion::Bishop;
        break;
    case 'n':
    case 'k':
        move.promotion = Promotion::Knight;
        break;
    case 'r':
        move.promotion = Promotion::Rook;
        break;
    }
}

bool Board::handlePromotion(Square &source, Square &target, Move &move)
{
    source.piece->move(target);
    if (move.promotion == Promotion::None)
    {
        move.promotion = Promotion::Queen;
        // askUserForInput(move); // Unless specified the promotion will be queen.
        // This is automatic as the backandforth with the player should not be done
        // at nested levels. But may prove bad when playing.
    }
    switch (move.promotion)
    {
    case Promotion::Queen:
        if (transaction.sourcePcPtr->color == Color::white)
        {
            target.piece = new Queen(target.piece->color, target.apos, Piece_type::queen, "\u2655",
                                     &target, *this);
        }
        else
        {
            target.piece = new Queen(target.piece->color, target.apos, Piece_type::queen, "\u265B",
                                     &target, *this);
        }
        break;
    case Promotion::Bishop:
        if (transaction.sourcePcPtr->color == Color::white)
        {
            target.piece = new Bishop(target.piece->color, target.apos, Piece_type::bishop, "\u2657",
                                      &target, *this);
        }
        else
        {
            target.piece = new Bishop(target.piece->color, target.apos, Piece_type::bishop, "\u265D",
                                      &target, *this);
        }
        break;
    case Promotion::Knight:
        if (transaction.sourcePcPtr->color == Color::white)
        {
            target.piece = new Knight(target.piece->color, target.apos, Piece_type::knight, "\u2658",
                                      &target, *this);
        }
        else
        {
            target.piece = new Knight(target.piece->color, target.apos, Piece_type::knight, "\u265E",
                                      &target, *this);
        }
        break;
    case Promotion::Rook:
        if (transaction.sourcePcPtr->color == Color::white)
        {
            target.piece = new Rook(target.piece->color, target.apos, Piece_type::knight, "\u2656",
                                    &target, *this);
        }
        else
        {
            target.piece = new Rook(target.piece->color, target.apos, Piece_type::knight, "\u265C",
                                    &target, *this);
        }
        break;
    default:
        return false;
        break;
    }
    return true;
}

void Board::createKings()
{

    getSquare("e1").piece = new King{Color::white, "e1", Piece_type::king, "\u2654",
                                     &getSquare("e1"), *this};

    getSquare("e8").piece = new King{Color::black, "e8", Piece_type::king, "\u265A",
                                     &getSquare("e8"), *this};
}

void Board::createQueens()
{

    getSquare("d1").piece = new Queen{Color::white, "d1", Piece_type::queen, "\u2655",
                                      &getSquare("d1"), *this};

    getSquare("d8").piece = new Queen{Color::black, "d8", Piece_type::queen, "\u265B",
                                      &getSquare("d8"), *this};
}

void Board::createBishops()
{

    getSquare("c1").piece = new Bishop{Color::white, "c1", Piece_type::bishop, "\u2657",
                                       &getSquare("c1"), *this};
    getSquare("f1").piece = new Bishop{Color::white, "f1", Piece_type::bishop, "\u2657",
                                       &getSquare("f1"), *this};

    getSquare("c8").piece = new Bishop{Color::black, "c8", Piece_type::bishop, "\u265D",
                                       &getSquare("c8"), *this};
    getSquare("f8").piece = new Bishop{Color::black, "f8", Piece_type::bishop, "\u265D",
                                       &getSquare("f8"), *this};
}

void Board::createKnights()
{
    getSquare("b1").piece = new Knight{Color::white, "b1", Piece_type::knight, "\u2658",
                                       &getSquare("b1"), *this};
    getSquare("g1").piece = new Knight{Color::white, "f1", Piece_type::knight, "\u2658",
                                       &getSquare("g1"), *this};

    getSquare("b8").piece = new Knight{Color::black, "c8", Piece_type::knight, "\u265E",
                                       &getSquare("b8"), *this};
    getSquare("g8").piece = new Knight{Color::black, "f8", Piece_type::knight, "\u265E",
                                       &getSquare("g8"), *this};
}

void Board::createRooks()
{
    getSquare("a1").piece = new Rook{Color::white, "a1", Piece_type::rook, "\u2656",
                                     &getSquare("a1"), *this};
    getSquare("h1").piece = new Rook{Color::white, "h1", Piece_type::rook, "\u2656",
                                     &getSquare("h1"), *this};

    getSquare("a8").piece = new Rook{Color::black, "a8", Piece_type::rook, "\u265C",
                                     &getSquare("a8"), *this};
    getSquare("h8").piece = new Rook{Color::black, "h8", Piece_type::rook, "\u265C",
                                     &getSquare("h8"), *this};
}

void Board::createPawns()
{
    for (char i = 'a'; i != 'i'; i = static_cast<char>(i + 1))
    {
        std::string white_pawn;
        white_pawn.push_back(i);
        white_pawn += "2";

        getSquare(white_pawn).piece = new Pawn{Color::white, white_pawn, Piece_type::pawn, "\u2659",
                                               &getSquare(white_pawn), *this};

        std::string black_pawn;
        black_pawn.push_back(i);
        black_pawn += "7";
        getSquare(black_pawn).piece = new Pawn{Color::black, black_pawn, Piece_type::pawn, "\u265F",
                                               &getSquare(black_pawn), *this};
    }
}

std::string Board::determineCastlingRook(const Square &source, const Square &target) const
{
    if (source.piece->color == Color::white)
    {
        if (target.apos == "c1")
        {
            return "a1";
        }
        else if (target.apos == "g1")
        {
            return "h1";
        }
    }
    else
    {
        if (target.apos == "c8")
        {
            return "a8";
        }
        else if (target.apos == "g8")
        {
            return "h8";
        }
    }

    return "WRONG";
}