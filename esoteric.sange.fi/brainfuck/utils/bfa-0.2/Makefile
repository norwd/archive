include config
DIRS=bfa contrib examples
all:
	set -e ; for d in $(DIRS) ; do $(MAKE) -C $$d ; done
clean:
	set -e ; for d in $(DIRS) ; do $(MAKE) clean -C $$d ; done
install:
	set -e ; for d in $(DIRS) ; do $(MAKE) install -C $$d ; done
	install -D -o root -g root -m 0644 README ${DOCDIR}/README
	install -D -o root -g root -m 0644 readme.html ${DOCDIR}/readme.html
uninstall:
	set -e ; for d in $(DIRS) ; do $(MAKE) uninstall -C $$d ; done
	rm -fr ${DOCDIR}
