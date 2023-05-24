all: bin/main.exe

bin/main.exe: obj/main.o obj/cell.o obj/displaySDL.o obj/vec2f.o obj/world.o
	g++ -o bin/main.exe obj/cell.o obj/main.o obj/displaySDL.o obj/vec2f.o obj/world.o -lSDL2 -lSDL2_image -lSDL2_ttf

obj/main.o: src/main.cpp include/DisplaySDL.hpp
	g++ -c src/main.cpp -o obj/main.o -I include

obj/cell.o: src/cell.cpp include/Cell.hpp include/Utils.hpp include/Vec2f.hpp
	g++ -c src/cell.cpp -o obj/cell.o -I include

obj/displaySDL.o: src/displaySDL.cpp include/DisplaySDL.hpp include/Utils.hpp include/World.hpp
	g++ -c src/displaySDL.cpp -o obj/displaySDL.o -I include -I /usr/include/SDL2

obj/vec2f.o: src/vec2f.cpp include/Vec2f.hpp
	g++ -c src/vec2f.cpp -o obj/vec2f.o -I include

obj/world.o: src/world.cpp include/World.hpp include/Cell.hpp
	g++ -c src/world.cpp -o obj/world.o -I include

clean:
	rm -f obj/*.o
	rm -f bin/*.exe