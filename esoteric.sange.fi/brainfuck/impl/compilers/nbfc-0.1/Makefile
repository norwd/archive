all: compiler.o y.tab.o lex.yy.o 
	gcc -Wall -O4 -g -o nbfc compiler.o lex.yy.o y.tab.o -lfl

lex.yy.o: bf.l
	flex bf.l
	gcc -c lex.yy.c

y.tab.o: bf.y
	bison -yd bf.y
	gcc -c y.tab.c

compiler.o: compiler.c
	gcc -c compiler.c

install: 
	install -c nbfc /usr/bin/nbfc 
	install -c nbfc.1 /usr/man/man1/nbfc.1

clean:
	rm -f *.o
	rm -f y.tab.* lex.yy.*
	rm -f bf.out*
	rm -f *.java 
	rm -f *.class
	rm -f *~
	rm -f nbfc 
