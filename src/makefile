projet: clean spell.o spellCheck.o projet.o
	gcc-4.6 -O3 spell.o spellCheck.o projet.o -o projet -lm libisentlib.a -lglut -lX11

spell.o: spell.c spell.h
	gcc-4.6 -O3 -w -c spell.c
	
spellCheck.o: spellCheck.c spellCheck.h
	gcc-4.6 -O3 -w -c spellCheck.c -lX11
	
projet.o: projet.c projet.h spell.h
	gcc-4.6 -O3 -c projet.c


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
