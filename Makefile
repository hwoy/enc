cc = gcc
CFLAGS = -O2 -std=c89 -pedantic -Wall -DANSI


.PHONY: all clean

all: enc
enc: main.o main1.o enc.o grap.o
	$(cc) -o enc main.o enc.o grap.o && $(cc) -o denc main1.o enc.o grap.o
main.o: main.c enc.h main.h
	$(cc) -c $(CFLAGS) main.c
main1.o: main1.c enc.h main.h
	$(cc) -c $(CFLAGS) main1.c
enc.o: enc.c enc.h
	$(cc) -c $(CFLAGS) enc.c

clean:
	rm -f enc denc main.o main1.o enc.o denc.o *~ *.en

