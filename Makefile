#
# Author: Tiago Augusto Pimenta <tiagoapimenta@gmail.com>
#

TARGET  = x-shooter

SOURCES = x-shooter.cpp api/graphic.cpp game.cpp # image.cpp

#SOURCES = x-shooter.cpp game.cpp screen.cpp audio.cpp image.cpp font.cpp \
#          hud.cpp world.cpp level.cpp hero.cpp enemy.cpp shot.cpp item.cpp

OBJS    = $(SOURCES:.cpp=.o)

CFLAGS  = -O3 `pkg-config --cflags sdl SDL_image SDL_mixer`
LDFLAGS =

LIBS    = -lSDL_ttf `pkg-config --libs sdl SDL_image SDL_mixer`

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	@rm $(TARGET) $(OBJS)
