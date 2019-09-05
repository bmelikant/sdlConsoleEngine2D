CFLAGS:=$(shell pkg-config --cflags sdl2) -Iinclude -I/usr/include/SDL2
LDFLAGS:=$(shell pkg-config --libs sdl2)

ENGINE_ARCHIVE := libSDLEngine.a
ENGINE_OBJECTS:=\
	src/sdlConsoleEngine2D.o \
	src/sdlConsoleRenderer2D.o

all: engine

.PHONY: all clean

engine: $(ENGINE_ARCHIVE)

%.a: $(ENGINE_OBJECTS)
	$(AR) r $@ $(ENGINE_OBJECTS)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o $(ENGINE_ARCHIVE)