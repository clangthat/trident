CXX := g++
SRC_DIR := src
INCLUDE_DIR := includes
BUILD_DIR := build
TARGET := main

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

CXXFLAGS := -I$(INCLUDE_DIR) -std=c++17 -Wall -Wextra -Werror -pedantic -g
LDFLAGS := -lstdc++

ifeq ($(DEBUG),1)
    CXXFLAGS += -DDEBUG
endif

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $^ -o build/$@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean