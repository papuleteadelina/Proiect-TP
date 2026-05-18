# Makefile pentru Simon Says

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Regula principala
all: simon_says

# Crearea executabilului
simon_says: main.o simon.o
	$(CC) $(CFLAGS) -o simon_says main.o simon.o

# Compilarea main.c
main.o: main.c simon.h
	$(CC) $(CFLAGS) -c main.c

# Compilarea simon.c
simon.o: simon.c simon.h
	$(CC) $(CFLAGS) -c simon.c

# Regula pentru stergerea fisierelor compilate
clean:
	rm -f *.o simon_says
