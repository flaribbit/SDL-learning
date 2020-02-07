CC=g++
CFLAGS=-s -O2 -DNDEBUG -I include

a.exe: main.o Image.o Sprite.o
	$(CC) main.o Image.o Sprite.o $(CFLAGS)
main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS)
Image.o: Image.cpp
	$(CC) -c Image.cpp $(CFLAGS)
Sprite.o: Sprite.cpp
	$(CC) -c Sprite.cpp $(CFLAGS)
