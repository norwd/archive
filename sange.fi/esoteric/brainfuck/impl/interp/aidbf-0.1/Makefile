include CONFIG
DIRS=source
all:
	set -e ; for d in $(DIRS) ; do $(MAKE) -C $$d ; done
clean:
	set -e ; for d in $(DIRS) ; do $(MAKE) clean -C $$d ; done
install: all
	set -e ; for d in $(DIRS) ; do $(MAKE) install -C $$d ; done
uninstall:
	set -e ; for d in $(DIRS) ; do $(MAKE) uninstall -C $$d ; done
