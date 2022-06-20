#include "pgnParser.h"

PgnParser::PgnParser()
{
}

PgnParser::PgnParser(std::string matchContent)
{

    std::regex whiteWinner("Result \"1-0\"");
    std::regex whiteLose("Result \"0-1\"");
    std::regex stalemate("Result \"1/2-1/2\"");

    if (std::regex_search(matchContent, whiteWinner))
    {
        result = Winner::white;
    }
    else if (std::regex_search(matchContent, whiteLose))
    {
        result = Winner::black;
    }
    else if (std::regex_search(matchContent, stalemate))
    {
        result = Winner::stalemate;
    }
    else
    {
        throw;
    }

    // Regex in cpp is really fucking ugly.
    size_t startOfGame = matchContent.find("1. ");
    //, matchContent.size()-startOfGame

    std::string temp = matchContent.substr(startOfGame);

    std::regex stripper("[0-9]+\\.[ |\n]");

    std::string stripped;
    std::regex_replace(std::back_inserter(stripped), temp.begin(), temp.end(), stripper, "");

    std::istringstream iss(stripped);
    std::vector<std::string> movesStr(std::istream_iterator<std::string>{iss},
                                      std::istream_iterator<std::string>());
    for (auto moveStr : movesStr)
    {
        Move move = convertStringToMove(moveStr);
        if (move.longAlg != NOT_APPLICABLE)
        {
            moves.push_back(move);
        }
    }
}

Move PgnParser::convertStringToMove(std::string pgnString)
{
    Move move;

    if (pgnString.size() < 4 || pgnString.size() > 5)
    {
        std::cout<<"something went wrong with parsing the pgnString: "<<pgnString<<std::endl;
        move.longAlg = NOT_APPLICABLE;
        return move;
    }

    move.longAlg = pgnString;
    move.source = pgnString.substr(0, 2);
    move.target = pgnString.substr(2, 2);

    move.promotion = Promotion::None;
    move.isCheckingMove = false;

    if (pgnString.size() == 5)
    {
        move.isCheckingMove = (pgnString.substr(4, 1) == "+") ? true : false;

        std::string promotionString = pgnString.substr(4, 1);
        
        // Cant make this into a switch :(
        if(promotionString == "q")
        {
            move.promotion = Promotion::Queen;
        }
        else if (promotionString == "b")
        {
            move.promotion = Promotion::Bishop;
        }
        else if (promotionString == "n")
        {
            move.promotion = Promotion::Knight;
        }
        else if (promotionString == "r")
        {
            move.promotion = Promotion::Rook;
        }
        // TODO might need to add # as check mate for last move. We'll see. 
        // else
        // {
        //     move.promotion = Promotion::none;
        // }
    }
    return move;
}