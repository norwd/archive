include ../CONFIG
CC=gcc
DEFINES=-DDATASEGSIZE=${DATASEGSIZE}
all: aidbf aidbf.1.gz
aidbf: aidbf.c
	${CC} ${DEFINES} aidbf.c -o aidbf
aidbf.1.gz: aidbf.1
	cat aidbf.1 | gzip > aidbf.1.gz
clean:
	rm -f aidbf
	rm -f aidbf.1.gz
install:
	install -D aidbf ${BINDIR}/aidbf
	install -D -o root -g root -m 0644 aidbf.1.gz ${MANDIR}/man1/aidbf.1.gz
uninstall:
	rm -f ${BINDIR}/aidbf
	rm -f ${MANDIR}/man1/aidbf.1.gz
