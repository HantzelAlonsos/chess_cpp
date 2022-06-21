    #include <stdio.h>
#include <stdlib.h>


#include "gtest/gtest.h"

#include "game.h"

TEST(enPassant, EnPassantWorks){
  Game myGame;
  myGame.render();

  std::string array[] = {"e2e4", "e4e5", "d7d5", "e5d6"};
  for (auto it : array){
    std::cout<<it<<std::endl;
    assert(myGame.move(it));
    myGame.render();
  }
  
}


TEST(enPassant, EnPassantFails){
  Game myGame;
  myGame.render();

  std::string array[] = {"e2e4", "e4e5", "d7d5", "h2h4", "h7h5"};
  for (auto it : array){
    std::cout<<it<<std::endl;
    ASSERT_TRUE(myGame.move(it));
    myGame.render();
  }
  ASSERT_FALSE(myGame.move("e5d6"));
  
}

TEST(enPassant, DoubleEnPassant){
  Game myGame;
  myGame.render();

  std::string array[] = {"e2e4", "e4e5", "d7d5", "h2h4", "h4h5", "g7g5", "h5g6"};
  for (auto it : array){
    std::cout<<it<<std::endl;
    ASSERT_TRUE(myGame.move(it));
    myGame.render();
  }
  
}

TEST(enPassant, DoubleEnPassantFailure){
  Game myGame;
  myGame.render();

  std::string array[] = {"e2e4", "e4e5", "d7d5", "h2h4", "h4h5", "g7g5", "h5g6"};
  for (auto it : array){
    std::cout<<it<<std::endl;
    ASSERT_TRUE(myGame.move(it));
    myGame.render();
  }
  ASSERT_FALSE(myGame.move("e5d6"));
}

TEST(check, kingInCheckOtherMove){
  Game myGame;
  myGame.render();
  // try a unsupported scholars mate
  std::string array[] = {"e2e4", "d1h5", "h5f7"};
  for (auto it : array){
    std::cout<<it<<std::endl;
    ASSERT_TRUE(myGame.move(it));
    myGame.render();
  }
  ASSERT_FALSE(myGame.move("a7a5"));  
}

TEST(check, getOutOfCheck){
  Game myGame;
  myGame.render();
  // try a unsupported scholars mate
  std::string array[] = {"e2e4", "d1h5", "h5f7", "e8f7"};
  for (auto it : array){
    std::cout<<it<<std::endl;
    ASSERT_TRUE(myGame.move(it));
    myGame.render();
  }
  ASSERT_FALSE(myGame.gameOver());
}

TEST(mate, scholarsMate){
  Game myGame;
  myGame.render();
  // try a unsupported scholars mate
  std::string array[] = {"e2e4", "d1h5", "f1c4" , "h5f7"};
  for (auto it : array){
    std::cout<<it<<std::endl;
    ASSERT_TRUE(myGame.move(it));
    myGame.render();
  }
  ASSERT_TRUE(myGame.gameOver());
}