SDIR=src
CC=gcc
CFLAGS=

ODIR=obj
BDIR=bin

LIBS=-lm

%.c: %.y
%.c: %.l

_TST_LOGO = logo.o test_logo.o
TST_LOGO = $(patsubst %,$(ODIR)/%,$(_TST_LOGO))

_TST_LEX = logo.o logo.tab.o logo.yy.o
TST_LEX = $(patsubst %,$(ODIR)/%,$(_TST_LEX))

all: clean $(BDIR)/test_logo $(BDIR)/test_lexer
	$(BDIR)/test_logo

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(SDIR)/logo.yy.c: $(SDIR)/logo.l $(SDIR)/logo.tab.h
	flex -o $@ $^

$(SDIR)/logo.tab.c: $(SDIR)/logo.y
	bison -d --defines=$(SDIR)/logo.tab.h -o $@ $^

$(SDIR)/logo.tab.h: $(SDIR)/logo.tab.c

$(BDIR)/test_logo: $(TST_LOGO)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

$(BDIR)/test_lexer: $(TST_LEX)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
	rm -rf $(BDIR)/*
	rm -f src/*.tab.c src/*.yy.c src/logo.tab.h