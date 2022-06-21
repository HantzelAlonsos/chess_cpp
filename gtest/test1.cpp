    #include <stdio.h>
#include <stdlib.h>


#include "gtest/gtest.h"

#include "chess.h"

TEST(enPassant, EnPassantWorks){
  Game myGame;
  myGame.render();

  std::string array[] = {"e2e4", "e4e5", "d7d5", "e5d6"};
  for (auto it : array){
    assert(myGame.move(it));
    myGame.render();
  }
  
}


TEST(enPassant, EnPassantFails){
  Game myGame;
  myGame.render();

  std::string array[] = {"e2e4", "e4e5", "d7d5", "h2h4", "h7h5"};
  for (auto it : array){
    ASSERT_TRUE(myGame.move(it));
    myGame.render();
  }
  ASSERT_FALSE(myGame.move("e5d6"));
  
}

