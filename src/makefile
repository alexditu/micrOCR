projet: clean
	gcc-4.6 -O3 projet.c BmpLib.c OutilsLib.c -o projet -lm
	
projet.o: projet.c projet.h spell.h BmpLib.o
	gcc-4.6 -O3 -c projet.c BmpLib.c

BmpLib.o: OutilsLib.o
	gcc-4.6 -Wall -O2 -c BmpLib.c OutilsLib.o -g

OutilsLib.o:
	gcc-4.6 -Wall -O2 -c OutilsLib.c -g

debug: clean
	gcc-4.6 -g -c spell.c -Wall -Wextra
	gcc-4.6 -g -c spellCheck.c -Wall -Wextra
	gcc-4.6 -g -c projet.c -Wall -Wextra
	gcc-4.6 -fsanitize=address -fno-omit-frame-pointer -g -Wall -Wextra spell.o spellCheck.o projet.o -o projet -lm libisentlib.a -lglut -lX11

graph: clean
	gcc-4.6 -g -fdump-rtl-expand -c projet.c
	egypt $(CURDIR)/projet.c.*.expand | dot -Tpng -o graph.png

clean:
	rm -f *~ *.o *.expand *.ps graph.png projet
