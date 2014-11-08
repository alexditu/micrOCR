exemple: exemple.c libisentlib.a
	gcc-4.6 -Wall exemple.c -o exemple -lm libisentlib.a -lglut -lX11
	
# Sous MacOSX, remplacer la ligne de commande ci-dessus par la suivante :
#	gcc-4.6 -Wall exemple.c -o exemple -lm libisentlib.a -framework OpenGL -framework GLUT

libisentlib.a: BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o VectorLib.o WavLib.o
	ar r libisentlib.a BmpLib.o ErreurLib.o ESLib.o GfxLib.o OutilsLib.o SocketLib.o ThreadLib.o VectorLib.o WavLib.o
	ranlib libisentlib.a

BmpLib.o: BmpLib.c BmpLib.h OutilsLib.h
	gcc-4.6 -Wall -O2 -c BmpLib.c -g

ErreurLib.o: ErreurLib.c ErreurLib.h
	gcc-4.6 -Wall -O2 -c ErreurLib.c -g

ESLib.o: ESLib.c ESLib.h ErreurLib.h
	gcc-4.6 -Wall -O2 -c ESLib.c -g

GfxLib.o: GfxLib.c GfxLib.h ESLib.h
	gcc-4.6 -Wall -O2 -c GfxLib.c -I/usr/include/GL -lX11 -g

OutilsLib.o: OutilsLib.c OutilsLib.h
	gcc-4.6 -Wall -O2 -c OutilsLib.c -g

SocketLib.o: SocketLib.c SocketLib.h
	gcc-4.6 -Wall -O2 -c SocketLib.c -g

ThreadLib.o: ThreadLib.c ThreadLib.h
	gcc-4.6 -Wall -O2 -c ThreadLib.c -g

VectorLib.o: VectorLib.c VectorLib.h
	gcc-4.6 -Wall -O2 -c VectorLib.c -msse3 -g

WavLib.o: WavLib.c WavLib.h OutilsLib.h
	gcc-4.6 -Wall -O2 -c WavLib.c -Wno-unused-result -g

clean:
	rm -f *~ *.o libisentlib.a
