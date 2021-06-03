CC=gcc
CFLAGS=-Wall -g
DEPS = dintegerarray.h solutions.h constants.h tri.h interface.h btree.h
ODIR = obj
LIBS = -lm

_OBJ=main.o dintegerarray.o solutions.o donnees.o tri.o interface.o btree.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -g -o $@ $< $(CFLAGS)
	
executable: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	
