# chess_cpp
A stupid chess game I made

En passant, castling and promotions all implemented. The 3 repetition is not implemented.

Game uses long algebraic notation as input but can also be setup to parse pgn tho this also needs to be converted to long algebraic. There are a few hundred games converted to long algebraic notation in the test folder which you can setup to be run.

make test runs one of these games.
make gtest runs a number of gtests.

The board is 0 indexed tho pieces are 1 indexed. This is a bit confusing but it is how chess does things. Dunno how to fix this issue.

https://docs.google.com/presentation/d/1qIUNKgGxlLzVf0da-126527yY67QzgrSPHMrTK324C4/edit#slide=id.p