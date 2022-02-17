CC      = gcc
INCLDIR = include/
BINDIR  = bin/
#OBJDIR  = obj/
SRCDIR  = src/

_BIN    = fuzzer
BIN     = $(addprefix $(BINDIR), $(_BIN))

SRC     = $(wildcard src/*.c)
INCL    = $(wildcard include/*.h)
_OBJS   = $(patsubst src/%.c, %.o, $(SRC))
OBJS    = $(addprefix $(BINDIR), $(_OBJS))


all: $(BIN)

$(BIN): $(BINDIR) runner main
	$(CC) $(OBJS) -o $(BIN)

$(BINDIR):
	mkdir -p $(BINDIR)

#$(OBJDIR):
#	mkdir -p $(OBJDIR)

main : src/main.c
	$(CC) -c -o bin/main.o src/main.c
  
runner : src/runner.c
	$(CC) -c -o bin/runner.o src/runner.c
  
clean:
	rm -rf $(BINDIR) $(OBJDIR) test/test_atoi

test: $(BIN)
	gcc test/test_atoi.c -o bin/test_atoi
	gcc test/test_timeout.c -o bin/test_timeout
