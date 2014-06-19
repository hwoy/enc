cc = gcc
CFLAGS = -O2 -std=c89 -pedantic -Wall -DANSI


.PHONY: all clean require

all: enc
enc: main.o main1.o enc.o grap/grap.o
	$(cc) -o enc main.o enc.o grap/grap.o && $(cc) -o denc main1.o enc.o grap/grap.o
main.o: main.c enc.h main.h
	$(cc) -c $(CFLAGS) main.c
main1.o: main1.c enc.h main.h
	$(cc) -c $(CFLAGS) main1.c
enc.o: enc.c enc.h
	$(cc) -c $(CFLAGS) enc.c

require:
	git clone https://github.com/hwoy/grap.git && make -C grap


clean:
	rm -f enc denc main.o main1.o enc.o denc.o *~ *.en

