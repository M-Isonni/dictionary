CC=clang
CPPCHECK=C:\Program Files\Cppcheck\cppcheck.exe
CFLAGS=-Wall -Werror -Iinclude -Wno-pragma-pack
LDFLAGS=-L. -lSDL2
BINARY_TESTS=run_tests.exe

all: run_tests.exe

run_tests.exe: tests.o dictionary.o
	$(CC) -o $(BINARY_TESTS) $^
	./$(BINARY_TESTS)

tests.o: tests.c aiv_unit_test.h
	$(CC) -c -o $@ $(CFLAGS) $<

dictionary.o: dictionary.c dictionary.h
	$(CC) -c -o $@ $(CFLAGS) $<
