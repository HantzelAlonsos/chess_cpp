# Main.cpp has the entrypoint.

# Shamelessly stolen makefiles lol

TARGET_EXEC := chess

BUILD_DIR := ./.build
SRC_DIRS := ./src

CPPFLAGS := -std=c++14
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')

# String substitution for every C/C++ file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

#INC_DIRS := $(shell find $(SRC_DIRS) -type d)
#INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS = -std=c++14

.PHONY: gtest
gtest: 
	g++ -Wall -g -pthread gtest/test1.cpp ./src/knight.cpp ./src/square.cpp ./src/pawn.cpp ./src/piece.cpp ./src/bishop.cpp ./src/king.cpp ./src/chess.cpp ./src/board.cpp ./src/queen.cpp ./src/pgnParser.cpp ./src/rook.cpp -lgtest_main -lgtest -lpthread -I./src

$(BUILD_DIR)/%.o: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET_EXEC)

run: $(TARGET_EXEC)
	./$(TARGET_EXEC)


test: $(TARGET_EXEC)
	./$(TARGET_EXEC) 1


build: clean $(TARGET_EXEC)