# Snipa
# macOS:  make
# Windows (MSYS2 MinGW): make
#   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-freeglut mingw-w64-x86_64-openal-soft

CXX      ?= g++
CXXFLAGS ?= -O2 -Wall -Wno-deprecated-declarations
SRCS      = main.cpp BMPLoader.cpp

ifeq ($(OS),Windows_NT)
  TARGET = SniperFinal.exe
  CXXFLAGS += -DGLUT_DISABLE_ATEXIT_HACK
  LIBS = -lfreeglut -lglu32 -lopengl32 -lopenal
else
  UNAME := $(shell uname -s)
  ifeq ($(UNAME),Darwin)
    TARGET = snipa
    LIBS = -framework OpenGL -framework GLUT -framework OpenAL -framework Cocoa -framework CoreGraphics
  else
    TARGET = snipa
    LIBS = -lGL -lGLU -lglut -lopenal
  endif
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

clean:
	rm -f snipa SniperFinal.exe
