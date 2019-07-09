# Change the following values to suit your system.

CFLAGS=`sdl-config --cflags` -W -Wall -ggdb -O2
SDL_LIB=`sdl-config --libs` -lSDL_ttf

CCC=g++

OBJECTS =

run: main.o $(OBJECTS) 
	$(CCC) $(CFLAGS) main.cpp -o run $(OBJECTS) $(SDL_LIB)

main.o: main.cpp
	$(CCC) $(CFLAGS) -c main.cpp

clean:
	rm -f *.o run
	rm -f *~
