#
# Author: Tiago Augusto Pimenta <tiagoapimenta@gmail.com>
#

TARGET  = bin/x-shooter

SOURCES = $(patsubst %,src/%.cpp,x-shooter api/graphic game screen image grid \
          cache)

#audio.cpp font.cpp hud.cpp world.cpp level.cpp hero.cpp enemy.cpp shot.cpp item.cpp

OBJS    = $(SOURCES:src/%.cpp=.objs/%.o)

CFLAGS  = -O3 `pkg-config --cflags sdl SDL_image SDL_mixer` # -D_GNU_SOURCE=1 -D_REENTRANT -I/usr/include/SDL
LDFLAGS =

LIBS    = -lSDL_ttf `pkg-config --libs sdl SDL_image SDL_mixer` # -lSDL_image -lSDL_mixer -lSDL

all: $(TARGET)

$(TARGET): dirs $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)

.objs/%.o: src/%.cpp
	$(CXX) $(CFLAGS) -c $? -o $@

dirs:
	-mkdir -p $(dir $(TARGET) $(OBJS))

clean:
	-rm $(TARGET) $(OBJS)
	-rmdir -p $(dir $(TARGET) $(OBJS))
