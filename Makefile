CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: asteroids

asteroids: asteroids.cpp log.cpp timers.cpp skaing.cpp nleyvarodrig.cpp jflanders.cpp rverduzcogui.cpp jsanchezcasa.cpp jsanchezcasa.h skaing.h rverduzcogui.h
	g++ $(CFLAGS) skaing.cpp asteroids.cpp log.cpp timers.cpp nleyvarodrig.cpp jflanders.cpp rverduzcogui.cpp jsanchezcasa.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -oasteroids

clean:
	rm -f asteroids
	rm -f *.o

