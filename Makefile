CC=gcc
CFLAGS=-Wall -Wextra

OBJS=main.o

main.exe:$(OBJS)
	mkdir -p "factures"
	$(CC) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS) *.exe

reset: clean
	$(RM) factures/*