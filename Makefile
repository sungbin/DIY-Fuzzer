CC      = clang
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

$(BIN): $(BINDIR) runner main trace
	$(CC) $(OBJS) -fsanitize=address -g -o $(BIN)

$(BINDIR):
	mkdir -p $(BINDIR)

runner : src/runner.c
	$(CC) -g -c -o bin/runner.o src/runner.c
  
main : src/main.c
	$(CC) -g -c -o bin/main.o src/main.c

trace : src/trace-pc.c
	$(CC) -fsanitize=address -g -o bin/trace-pc.o -c src/trace-pc.c 

clean:
	rm -rf $(BINDIR)

test: $(BIN)
	$(CC) test/test_c_with_one_input/atoi.c -g -o bin/test_atoi
	$(CC) test/test_c_with_one_input/timeout.c -g -o bin/test_timeout
	$(CC) -g -fsanitize=address -fsanitize-coverage=trace-pc-guard -o bin/test_triangle test/test_c_with_three_input/triangle.c bin/trace-pc.o
