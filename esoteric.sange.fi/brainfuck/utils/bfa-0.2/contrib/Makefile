include ../config
CC=gcc
all: bfi
bfi: bfi.c
	${CC} bfi.c -o bfi
clean:
	rm -f bfi
install:
	install -D bfi ${BINDIR}/bfi
uninstall:
	rm -f ${BINDIR}/bfi
