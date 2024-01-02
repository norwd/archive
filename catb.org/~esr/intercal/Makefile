SRC = /usr/local/src/perl
GLOBINCS = 
LOCINCS = 
LIBS =

iperl: $(SRC)/uperl.o usersub.o ical.o
	cc $(SRC)/uperl.o usersub.o ical.o $(LIBS) -lm -o iperl

usersub.o: usersub.c
	cc -c -I$(SRC) $(GLOBINCS) -DDEBUGGING -g usersub.c

ical.o: ical.c
	cc -c -I$(SRC) $(GLOBINCS) -DDEBUGGING -g ical.c

ical.c: $(SRC)/usub/mus ical.mus
	$(SRC)/usub/mus ical.mus >ical.c

test:	iperl op.ical
	./iperl op.ical

install:
	@echo "If you want to install this, you need to contact a phrenologist"
	@echo "(i.e. get your head examined!)"
