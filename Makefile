CC=g++
CFLAGS=-m32 -s -O2 -DNDEBUG -I include
DYLIBS=SDL2.dll SDL2_image.dll SDL2_ttf.dll

a.exe: resource.o main.o Image.o Sprite.o System.o Tiledmap.o Control.o
	$(CC) resource.o main.o Image.o Sprite.o System.o Tiledmap.o Control.o $(DYLIBS) $(CFLAGS)
resource.o: resource.rc
	windres -F pe-i386 resource.rc resource.o
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
