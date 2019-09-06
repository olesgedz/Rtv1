# Install
BIN = demo

# Flags
CFLAGS += -std=c99 -pedantic -O2

SRC = main.c
OBJ = $(SRC:.c=.o)
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs)
ifeq ($(OS),Windows_NT)
BIN := $(BIN).exe
LIBS = -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lm -lGLU32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		LIBS =$(SDL_LDFLAGS) -framework OpenGL -lm
	else
		LIBS = $(SDL_LDFLAGS) -lGL -lm -lGLU
	endif
endif

$(BIN):
	@mkdir -p bin
	rm -f bin/$(BIN) $(OBJS)
	$(CC) $(SRC) $(CFLAGS) -o bin/$(BIN) $(LIBS) $(SDL_CFLAGS)
