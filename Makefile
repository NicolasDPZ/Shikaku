CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
SRC_DIR  = src
OBJ_DIR  = build

SOURCES  = $(wildcard $(SRC_DIR)/*.cxx)
OBJECTS  = $(patsubst $(SRC_DIR)/%.cxx, $(OBJ_DIR)/%.o, $(SOURCES))
TARGET   = shikaku

.PHONY: all clean

all: $(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
