
CC = gcc
FLAGS = -g -O0

wemix.o:	wemix.c wemix.h hardware.h
	$(CC) $(FLAGS) wemix.c -c -o $@

AllocExperiment:	wemix.o AllocExperiment.c
	$(CC) $(FLAGS) $^ -o $@

.PHONY: clean

clean:
	rm -fr wemix.o AllocExperiment
