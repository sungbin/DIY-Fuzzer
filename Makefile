CC      = gcc
INCLDIR = include/
BINDIR  = bin/
OBJDIR  = obj/
SRCDIR  = src/

_BIN    = fuzzer
BIN     = $(addprefix $(BINDIR), $(_BIN))

SRC     = $(wildcard src/*.c)
INCL    = $(wildcard include/*.h)
_OBJS   = $(patsubst src/%.c, %.o, $(SRC))
OBJS    = $(addprefix $(OBJDIR), $(_OBJS))


all: $(BIN)

$(BIN): $(BINDIR) $(OBJDIR) runner main
	$(CC) $(OBJS) -o $(BIN)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

main : src/main.c
	$(CC) -c -o obj/main.o src/main.c
  
runner : src/runner.c
	$(CC) -c -o obj/runner.o src/runner.c
  
clean:
	rm -rf $(BINDIR) $(OBJDIR) test/test_atoi
