CC=gcc
CFLAGS=-Wall -Wextra

OBJS=topoffice.o
INCS=topoffice.h prod.h

all: topoffice.exe

topoffice.exe:$(OBJS)
	mkdir -p "factures"
	$(CC) -o $@ $^ -lm

%.o: %.c $(INCS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS) *.exe

reset: clean
	$(RM) factures/* ressources/alertes.txt ressources/nextFact
	cp ressources/stock.backup.txt ressources/stock.txt