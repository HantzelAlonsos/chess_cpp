# Chess.cpp has the entrypoint.

# Shamelessly stolen makefiles lol
BUILD_DIR := ./build
SRC_DIRS := ./src

CPPFLAGS := -std=c++14
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')

showMe:
	@echo "$(SRCS)"


build:
	$(CXX) $(CPPFLAGS) $(SRCS) -o "chess.game"

run: build
	./chess.game 

test: build
	./chess.game debugg
