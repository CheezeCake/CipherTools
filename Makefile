UTILSDIR=utils
SRCDIR=tools/src
BINDIR=tools/bin

CC=cc
CFLAGS=-W -Wall -std=c89 -pedantic -I$(UTILSDIR)
LDFLAGS=-lm


all: affine atbash baconian


utils.o: $(UTILSDIR)/utils.c
	$(CC) -c $(UTILSDIR)/utils.c -o $(UTILSDIR)/utils.o $(CFLAGS)


affine: affine.o utils.o
	$(CC) $(SRCDIR)/affine.o $(UTILSDIR)/utils.o -o $(BINDIR)/affine $(CFLAGS) $(LDFLAGS)

affine.o: tools/src/affine.c
	$(CC) -c $(SRCDIR)/affine.c -o $(SRCDIR)/affine.o $(CFLAGS) $(LDFLAGS)

atbash: atbash.o utils.o
	$(CC) $(SRCDIR)/atbash.o $(UTILSDIR)/utils.o -o $(BINDIR)/atbash $(CFLAGS) $(LDFLAGS)

atbash.o: $(SRCDIR)/atbash.c
	$(CC) -c $(SRCDIR)/atbash.c -o $(SRCDIR)/atbash.o $(CFLAGS) $(LDFLAGS)

baconian: baconian.o utils.o
	$(CC) $(SRCDIR)/baconian.o $(UTILSDIR)/utils.o -o $(BINDIR)/baconian $(CFLAGS) $(LDFLAGS)

baconian.o: $(SRCDIR)/baconian.c
	$(CC) -c $(SRCDIR)/baconian.c -o $(SRCDIR)/baconian.o $(CFLAGS) $(LDFLAGS)


clean:
	rm -f $(UTILSDIR)/utils.o
	rm -f $(SRCDIR)/affine.o
	rm -f $(SRCDIR)/atbash.o
	rm -f $(SRCDIR)/baconian.o

mrproper: clean
	rm -f $(BINDIR)/affine
	rm -f $(BINDIR)/atbash
	rm -f $(BINDIR)/baconian
