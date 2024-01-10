CC := gcc
CXX := g++
CFLAGS := -Wall -w -Iinclude
CXXFLAGS := $(CFLAGS)

ifeq ($(OS),Windows_NT)
    TARGET := $(BIN_DIR)/my_program.exe
    LDFLAGS += -mwindows -lglfw3 -lopengl32 -lglew32 -lSOIL
else
    TARGET := $(BIN_DIR)/my_program
    LDFLAGS += -lglfw -lGL -lm -lGLEW -lSOIL
endif

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

# Gather C source files
SRCS_C := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
OBJS_C := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS_C))

# Gather C++ source files
SRCS_CPP := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
OBJS_CPP := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS_CPP))

# Combine all object files
OBJS := $(OBJS_C) $(OBJS_CPP)

TARGET := $(BIN_DIR)/my_program

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
