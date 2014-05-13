UTILSDIR=utils
TOOLSDIR=tools

CC=cc
CFLAGS=-W -Wall -std=c89 -pedantic -I$(UTILSDIR)
LDFLAGS=-lm


all: affine atbash baconian


utils.o: $(UTILSDIR)/utils.c
	$(CC) -c $(UTILSDIR)/utils.c -o $(UTILSDIR)/utils.o $(CFLAGS)


affine: affine.o utils.o
	$(CC) $(TOOLSDIR)/affine/affine.o $(UTILSDIR)/utils.o -o $(TOOLSDIR)/affine/affine $(CFLAGS) $(LDFLAGS)

affine.o: $(TOOLSDIR)/affine/affine.c
	$(CC) -c $(TOOLSDIR)/affine/affine.c -o $(TOOLSDIR)/affine/affine.o $(CFLAGS) $(LDFLAGS)

atbash: atbash.o utils.o
	$(CC) $(TOOLSDIR)/atbash/atbash.o $(UTILSDIR)/utils.o -o $(TOOLSDIR)/atbash/atbash $(CFLAGS) $(LDFLAGS)

atbash.o: $(TOOLSDIR)/atbash/atbash.c
	$(CC) -c $(TOOLSDIR)/atbash/atbash.c -o $(TOOLSDIR)/atbash/atbash.o $(CFLAGS) $(LDFLAGS)

baconian: baconian.o utils.o
	$(CC) $(TOOLSDIR)/baconian/baconian.o $(UTILSDIR)/utils.o -o $(TOOLSDIR)/baconian/baconian $(CFLAGS) $(LDFLAGS)

baconian.o: $(TOOLSDIR)/baconian/baconian.c
	$(CC) -c $(TOOLSDIR)/baconian/baconian.c -o $(TOOLSDIR)/baconian/baconian.o $(CFLAGS) $(LDFLAGS)


clean:
	rm -f $(UTILSDIR)/utils.o
	rm -f $(TOOLSDIR)/affine/affine.o
	rm -f $(TOOLSDIR)/atbash/atbash.o
	rm -f $(TOOLSDIR)/baconian/baconian.o

mrproper: clean
	rm -f $(TOOLSDIR)/affine/affine
	rm -f $(TOOLSDIR)/atbash/atbash
	rm -f $(TOOLSDIR)/baconian/baconian
