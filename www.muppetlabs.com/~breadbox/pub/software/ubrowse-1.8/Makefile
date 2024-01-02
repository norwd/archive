# Makefile for ubrowse
#
# Note: "make clean-all" will force the next build to download the
# current Unicode standard.

CC = gcc
CFLAGS = -Wall -Wextra -Os
CFLAGS += $(shell pkg-config --cflags ncursesw)
LDFLAGS = -Wall -s
LDLIBS = $(shell pkg-config --libs ncursesw)
PREFIX = /usr/local

CHARLISTURL = https://www.unicode.org/Public/UNIDATA/UnicodeData.txt
BLOCKLISTURL = https://www.unicode.org/Public/UNIDATA/Blocks.txt

.PHONY: all clean clean-all install

all: ubrowse

ubrowse: ubrowse.o charlist.o blocklist.o
ubrowse.o: ubrowse.c data.h
charlist.o: charlist.c data.h
blocklist.o: blocklist.c data.h

charlist.c: mkcharlist.py
	curl $(CHARLISTURL) | ./mkcharlist.py > $@
blocklist.c: mkblocklist.py
	curl $(BLOCKLISTURL) | ./mkblocklist.py > $@

clean:
	rm -f ubrowse ubrowse.o charlist.o blocklist.o

clean-all: clean
	rm -f charlist.c blocklist.c

install: ubrowse
	install -d $(PREFIX)/bin
	install -d $(PREFIX)/share/man/man1
	install -m755 ./ubrowse $(PREFIX)/bin/
	install -m644 ./ubrowse.1 $(PREFIX)/share/man/man1/
