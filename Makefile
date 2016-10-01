prefix ?= /usr/local
exec_prefix ?= $(prefix)

bindir ?= $(exec_prefix)/bin
sbindir ?= $(exec_prefix)/sbin
libexecdir ?= $(exec_prefix)/libexec

datarootdir ?= $(prefix)/share
datadir ?= $(datarootdir)
sysconfdir ?= $(prefix)/etc
sharedstatedir ?= $(prefix)/com
localstatedir ?= $(prefix)/var
runstatedir ?= $(localstatedir)/run

includedir ?= /usr/local/include
oldincludedir ?= /usr/include
docdir ?= $(datarootdir)/doc/yourpkg.
infodir ?= /usr/local/share/info
htmldir?= $(docdir)
dvidir ?= $(docdir)
pdfdir ?= $(docdir)
psdir ?= $(docdir)
libdir ?= $(exec_prefix)/lib
lispdir ?= $(datarootdir)/emacs/site-lisp.

mandir ?= $(datarootdir)/man.
man1dir ?= $(mandir)/man1
man2dir ?= $(mandir)/man2
man3dir ?= $(mandir)/man3
man4dir ?= $(mandir)/man4
man5dir ?= $(mandir)/man5
man6dir ?= $(mandir)/man6
man7dir ?= $(mandir)/man7
man8dir ?= $(mandir)/man8

manext ?= .1
man1ext ?= .1
man2ext ?= .2
man3ext ?= .3
man4ext ?= .4
man5ext ?= .5
man6ext ?= .6
man7ext ?= .7
man8ext ?= .8

srcdir ?= $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

INSTALL ?= install
INSTALL_PROGRAM ?= $(INSTALL)
INSTALL_DATA ?= ${INSTALL} -m 644

MKDIR_P ?= mkdir -p

CFLAGS = -fPIC

.PHONY: all install uninstall clean

all: moot groot libuid.so

print-%: ; @echo $*=$($*)

install:
	$(INSTALL_PROGRAM) moot $(DESTDIR)$(bindir)/moot
	$(INSTALL_PROGRAM) groot $(DESTDIR)$(bindir)/groot
	$(INSTALL_PROGRAM) libuid.so $(DESTDIR)$(libdir)/libuid.so

uninstall:
	-rm -f $(DESTDIR)$(bindir)/moot

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

%.so: %.o
	$(CC) -shared $^ -o $@

libuid.so: libuid.o

clean:
	-rm -f *.o
	-rm -f *.so