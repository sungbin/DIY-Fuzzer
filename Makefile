CC      = gcc
INCLDIR = include/
BINDIR  = bin/
SRCDIR  = src/

_BIN    = main
BIN     = $(addprefix $(BINDIR), $(_BIN))

SRC     = $(wildcard src/*.c)
INCL    = $(wildcard include/*.h)
_OBJS   = $(patsubst src/%.c, %.o, $(SRC))
OBJS    = $(addprefix $(BINDIR), $(_OBJS))


all: $(BIN)

$(BIN): $(BINDIR) runner main
	$(CC) $(OBJS) -g -o $(BIN)

$(BINDIR):
	mkdir -p $(BINDIR)

runner : src/runner.c
	$(CC) -c -g -o bin/runner.o src/runner.c
  
main : src/main.c
	$(CC) -c -g -o bin/main.o src/main.c

clean:
	rm -rf $(BINDIR)

test: $(BIN)
	gcc test/test_c_with_one_input/atoi.c -g -o bin/test_atoi
	gcc test/test_c_with_one_input/timeout.c -g -o bin/test_timeout
