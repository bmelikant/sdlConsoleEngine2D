CFLAGS:=$(shell pkg-config --cflags sdl2 SDL2_ttf) -I../engine/include
LDFLAGS:=$(shell pkg-config --libs sdl2 SDL2_ttf)

all: engine-demo

.PHONY: all clean

engine-demo: main.o
	$(CXX) -o $@ $< ../engine/libSDLEngine.a $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o engine-demo