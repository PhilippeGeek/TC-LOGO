SDIR=src
CC=gcc
CFLAGS=

ODIR=obj
BDIR=bin

LIBS=

_TST_LOGO = logo.o test_logo.o
TST_LOGO = $(patsubst %,$(ODIR)/%,$(_TST_LOGO))

_TST_LEX = logo.o logo.bison.o logo.flex.o
TST_LEX = $(patsubst %,$(ODIR)/%,$(_TST_LEX))

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(SDIR)/logo.flex.c: $(SDIR)/logo.l $(SDIR)/tokens.h
	flex -o $@ $<

$(SDIR)/logo.bison.c: $(SDIR)/logo.y
	bison --defines=$(SDIR)/tokens.h -o $@ $<

$(SDIR)/tokens.h: $(SDIR)/logo.bison.c

$(BDIR)/test_logo: $(TST_LOGO)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

$(BDIR)/test_lexer: $(TST_LEX)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
	rm -rf $(BDIR)/*
	rm src/*.bison.c src/*.flex.c src/tokens.h