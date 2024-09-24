# Compiler flags
CFLAGS = -I/opt/homebrew/include -I./src -D_THREAD_SAFE -Wall -std=c99

# Linker flags
LDFLAGS =

# Libraries to link against
LDLIBS = -lSDL2 -lm

# Build rule
build:
	gcc $(CFLAGS) src/*.c -o renderer $(LDFLAGS) $(LDLIBS)

run:
	./renderer

clean:
	rm -f renderer
