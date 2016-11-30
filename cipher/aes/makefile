PROG = main
CC = gcc
LIB =
RM = rm -f
CFLAGS = -c -O2 -Wall

OBJS = \
  main.o \
  aes.o \

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(LDFLAGS) $(OBJS) $(LIB) $(LIB2)

main.o: main.c
	$(CC) $(CFLAGS) main.c

aes.o: aes.c
	$(CC) $(CFLAGS) aes.c

clean:
	-$(RM) $(PROG) $(OBJS)
