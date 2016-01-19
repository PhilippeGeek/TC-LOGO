SDIR=src
CC=gcc
CFLAGS=-g

ODIR=obj
BDIR=bin

LIBS=-lm
TESTS=tst/BASIC.logo tst/FLOAT.logo tst/PEN.logo tst/MANY-TESTS.logo tst/FLOWER.logo

%.c: %.y
%.c: %.l

_TST_LOGO = logo.o test_logo.o
TST_LOGO = $(patsubst %,$(ODIR)/%,$(_TST_LOGO))

_TST_LEX = logo.o logo.tab.o logo.yy.o
TST_LEX = $(patsubst %,$(ODIR)/%,$(_TST_LEX))

all: clean $(BDIR)/test_logo $(BDIR)/test_lexer
	@$(BDIR)/test_logo

$(ODIR)/%.o: $(SDIR)/%.c
	@echo -n 'Compiling $< ...'
	@$(CC) -c -o $@ $< $(CFLAGS)
	@echo ' Done'

$(SDIR)/logo.yy.c: $(SDIR)/logo.l $(SDIR)/logo.tab.h
	@echo -n 'Flexify our conditions ...'
	@flex -o $@ $^
	@echo ' Done'

$(SDIR)/logo.tab.c: $(SDIR)/logo.y
	@echo -n 'A bison is running ...'
	@bison -d --defines=$(SDIR)/logo.tab.h -o $@ $^
	@echo ' Done'

$(SDIR)/logo.tab.h: $(SDIR)/logo.tab.c

$(BDIR)/test_logo: $(TST_LOGO)
	@echo -n 'Link all for a little test ! ...'
	@gcc -o $@ $^ $(CFLAGS) $(LIBS)
	@echo ' Created'

$(BDIR)/test_lexer: $(TST_LEX)
	@echo -n 'Link all for a Lexer ! ...'
	@gcc -o $@ $^ $(CFLAGS) $(LIBS)
	@echo ' Created'

.PHONY: clean

clean:
	@rm -f $(ODIR)/*.o
	@rm -rf $(BDIR)/*
	@rm -f src/*.tab.c src/*.yy.c src/logo.tab.h
	@rm -f tst/*.svg

test: clean $(BDIR)/test_lexer
	@ echo -n "Testing "
	@ for i in $(TESTS); do \
	    echo -n '.';\
	    $(BDIR)/test_lexer < $$i > $$i.svg;\
	done
	@ echo '  Ended !'
