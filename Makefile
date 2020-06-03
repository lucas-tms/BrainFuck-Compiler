CFLAGS=-Wall

.PHONY: all clean superclean
all: brain

brain: bin/main.o bin/list.o bin/parser.o bin/asm.o bin/stack.o
	gcc -o $@ $^

bin/main.o: src/main.c
	@mkdir -p bin/
	gcc -c $< -o $@ $(CFLAGS)

bin/list.o: src/list.c src/list.h
	@mkdir -p bin/
	gcc -c $< -o $@ $(CFLAGS)

bin/parser.o: src/parser.c src/parser.h
	gcc -c $< -o $@ $(CFLAGS)

bin/asm.o: src/asm.c src/asm.h
	gcc -c $< -o $@ $(CFLAGS)

bin/stack.o: src/stack.c src/stack.h
	@mkdir -p bin/
	gcc -c $< -o $@ $(CFLAGS)

clean:
	rm -f bin/*

superclean: clean
	rm -f brain
