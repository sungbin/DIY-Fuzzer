CC = gcc
TARGET = fuzzer

$(TARGET) : runner.o main.o
	$(CC) -o $(TARGET) runner.o main.o

main.o : main.c
	$(CC) -c -o main.o main.c
  
runner.o : runner.c
	$(CC) -c -o runner.o runner.c
  
clean : 
	rm *.o rm ../test/*.txt fuzzer
