SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

TARGET = bin/roulette

CXX = g++

IDIR = include
CFLAGS = -pipe -O2 -g -Wall -std=c++11
CFLAGS += -I$(IDIR)

SRCCXX := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ += $(subst $(SRC_DIR)/, $(OBJ_DIR)/, $(SRCCXX:.cpp=.o))

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $< $(CFLAGS) -o $@

$(TARGET): $(OBJ)
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) $(OBJ) -o $@


clean:
	@rm -r $(BIN_DIR)
	@rm -r $(OBJ_DIR)
