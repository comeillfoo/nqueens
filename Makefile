SRCDIR=src
INCDIR=include
BUILDDIR=build

CC=gcc
CFLAGS=-pedantic -Wextra -Wall -std=gnu17 -I$(INCDIR)

LD=gcc
# LDFLAGS is not set yet


all: nqueens

nqueens: $(BUILDDIR)/main.o $(BUILDDIR)/resolver.o $(BUILDDIR)/bittricks.o
	$(LD) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(BUILDDIR)
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILDDIR):
	mkdir $(BUILDDIR)

.PHONY: clean

clean:
	rm -f ./nqueens
	rm -rf $(BUILDDIR)
