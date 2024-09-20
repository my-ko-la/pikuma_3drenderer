# Macos specific 
LDFLAGS=-I/opt/homebrew/include -D_THREAD_SAFE -lsdl2

build: 
	gcc $(LDFLAGS) -Wall -std=c99 src/*.c -o renderer

run: 
	./renderer

clean:
	rm renderer


