CPP=g++
SFML_LIB=-lsfml-graphics -lsfml-window -lsfml-system
SFML_AUDIO_LIB=-lsfml-audio
XML_LIB=-lpugixml

all: main.o
	$(CPP) $(XML_LIB) $(SFML_LIB) *.o -o nedowc
clear:
	rm *.o nedowc
run:
	./nedowc
game.o: map.o
	$(CPP) -c game.cpp -o game.o
main.o: game.o
	$(CPP) -c main.cpp -o main.o
animation.o:
	$(CPP) -c animation.cpp -o animation.o
unit.o: animation.o camera.o
	$(CPP) -c unit.cpp -o unit.o
map.o: unit.o collision.o
	$(CPP) -c map.cpp -o map.o
camera.o:
	$(CPP) -c camera.cpp -o camera.o
collision.o:
	$(CPP) -c collision.cpp -o collision.o
