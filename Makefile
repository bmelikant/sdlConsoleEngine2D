# root project Makefile
# build targets to build 

# accept all default make flags as-is
CFLAGS?=
CPPFLAGS?=
LDFLAGS?=
LIBS?=

# Make objects
ENGINE_OUTPATH:=engine/lib
ENGINE_LIBRARY:=libSDLengine.a
ENGINE_TARGET:=$(ENGINE_OUTPATH)/$(ENGINE_LIBRARY)

ENGINE_SRCDIR:=engine/src
DEMO_SRCDIR:=demo/src

ENGINE_OBJECTS:=\
	$(ENGINE_SRCDIR)/sdlConsoleEngine2D.o \
	$(ENGINE_SRCDIR)/sdlConsoleRenderer2D.o \
	$(ENGINE_SRCDIR)/shapes/shapeFactory.o \
	$(ENGINE_SRCDIR)/shapes/shape.o \
	$(ENGINE_SRCDIR)/shapes/triangle.o

DEMO_OBJECTS:=\
	$(DEMO_SRCDIR)/main.o \


# update the C flags and the Linker flags for SDL
CFLAGS:=$(CFLAGS) $(shell pkg-config --cflags sdl2 SDL2_ttf) -Iengine/include
LIBS:=$(LIBS) $(shell pkg-config --libs sdl2 SDL2_ttf)

.PHONY: all engine-demo engine clean clean-demo clean-engine

all: engine engine-demo

engine-demo: $(DEMO_OBJECTS) engine
	$(CXX) -o $@ $< $(ENGINE_TARGET) $(LDFLAGS) $(LIBS)

engine: $(ENGINE_TARGET)

$(ENGINE_TARGET): $(ENGINE_OBJECTS)
	$(shell mkdir -p $(ENGINE_OUTPATH))
	$(AR) r $@ $(ENGINE_OBJECTS)

.cpp.o:
	$(CXX) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean: clean-demo clean-engine

clean-demo:
	rm -f engine-demo
	rm -f $(DEMO_OBJECTS)

clean-engine:
	rm -f $(ENGINE_OBJECTS)
	rm -rf $(ENGINE_OUTPATH)