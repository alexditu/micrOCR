projet: clean spell.o spellCheck.o projet.o
	gcc -O3 spell.o spellCheck.o projet.o -o projet -lm libisentlib.a -lglut

spell.o: spell.c spell.h
	gcc -O3 -w -c spell.c
	
spellCheck.o: spellCheck.c spellCheck.h
	gcc -O3 -w -c spellCheck.c
	
projet.o: projet.c projet.h spell.h
	gcc -O3 -c projet.c


debug: clean
	clang -g -c spell.c -Wall -Wextra
	clang -g -c spellCheck.c -Wall -Wextra
	clang -g -c projet.c -Wall -Wextra
	clang -fsanitize=address -fno-omit-frame-pointer -g -Wall -Wextra spell.o spellCheck.o projet.o -o projet -lm libisentlib.a -lglut

graph: clean
	gcc -g -fdump-rtl-expand -c projet.c
	egypt $(CURDIR)/projet.c.*.expand | dot -Tpng -o graph.png

clean:
	rm -f *~ *.o *.expand *.ps graph.png projet
