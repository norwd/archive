include ../config
CC=gcc
all: bfa bfa.1.gz
bfa: bfa.c
	${CC} bfa.c -o bfa	
bfa.1.gz: bfa.1
	cat bfa.1 | gzip > bfa.1.gz	
clean:
	rm -f bfa
	rm -f bfa.1.gz
install:
	install -D bfa ${BINDIR}/bfa
	install -D -o root -g root -m 0644 bfa.1.gz ${MANDIR}/man1/bfa.1.gz
uninstall:
	rm -f ${BINDIR}/bfa
	rm -f ${MANDIR}/man1/bfa.1.gz
