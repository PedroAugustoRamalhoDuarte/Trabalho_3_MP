IDIR =../include
CC=g++
CFLAGS=-I $(IDIR)
ODIR=obj
LDIR =../lib

LIBS=-lm

_DEPS = contador_linhas.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = contador_linhas.o teste_contador.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

teste: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
