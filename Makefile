CC=gcc
CFLAGS=-Wall -Wextra

OBJS=main.o

all: main.exe

main.exe:$(OBJS)
	mkdir -p "factures"
	$(CC) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS) *.exe

reset: clean
	$(RM) factures/* ressources/alertes.txt ressources/nextFact
	cp ressources/stock.backup.txt ressources/stock.txt