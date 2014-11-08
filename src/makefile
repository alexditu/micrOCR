projet: clean projet.o
	gcc-4.6 -O3 projet.o BmpLib.o OutilsLib.o -o projet -lm -g
	
projet.o: BmpLib.o
	gcc-4.6 -O3 -c projet.c BmpLib.c

BmpLib.o: OutilsLib.o
	gcc-4.6 -Wall -O2 -c BmpLib.c -g

OutilsLib.o:
	gcc-4.6 -Wall -O2 -c OutilsLib.c -g

clean:
	rm -rf *.o projet
