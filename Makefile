TARGET = ping_pong

CXX = clang++

CXXFLAGS = -std=c++20 -Wall -g

SRC_DIR = src/
THIRD_PARTY = third_party/raylib

INCLUDES = -I$(THIRD_PARTY)/include

LDFLAGS = $(THIRD_PARTY)/lib/libraylib.a \
		-framework CoreVideo -framework IOKit -framework Cocoa \
		-framework OpenGL -framework CoreAudio -framework AudioToolbox

SRCS = $(SRC_DIR)/ping_pong.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: clean all
	./$(TARGET)
