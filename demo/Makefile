CFLAGS:=$(shell pkg-config --cflags sdl2) -I../engine/include
LDFLAGS:=$(shell pkg-config --libs sdl2)

all: engine-demo

.PHONY: all clean

demo: main.o
	$(CXX) -o $@ $< ../engine/libSDLEngine.a $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *.o engine-demo