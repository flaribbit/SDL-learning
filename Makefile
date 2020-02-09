CC=g++
CFLAGS=-m32 -s -O2 -DNDEBUG -I include
DYLIBS=SDL2.dll SDL2_image.dll SDL2_ttf.dll

a.exe: main.o Image.o Sprite.o System.o Tiledmap.o Control.o
	$(CC) main.o Image.o Sprite.o System.o Tiledmap.o Control.o $(DYLIBS) $(CFLAGS)
main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS)
Image.o: Image.cpp
	$(CC) -c Image.cpp $(CFLAGS)
Sprite.o: Sprite.cpp
	$(CC) -c Sprite.cpp $(CFLAGS)
System.o: System.cpp
	$(CC) -c System.cpp $(CFLAGS)
Tiledmap.o: Tiledmap.cpp
	$(CC) -c Tiledmap.cpp $(CFLAGS)
Control.o: Control.cpp
	$(CC) -c Control.cpp $(CFLAGS)
