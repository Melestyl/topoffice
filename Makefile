CC=gcc
CFLAGS=-Wall -Wextra

OBJS=main.o

main.exe:$(OBJS)
	$(CC) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS) main