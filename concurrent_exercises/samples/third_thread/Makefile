all:main

CC=g++
CPPFLAGS=-Wall -std=c++11 -ggdb
LDFLAGS=-pthread

main:main.o
	$(CC) $(LDFLAGS) -o $@ $^

main.o:main.cpp
	$(CC) $(CPPFLAGS) -o $@ -c $^

.PHONY:
	clean

clean:
	rm main.o main