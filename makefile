CC = gcc

CFLAGS = -ansi -Wall -g

# Include the current directory for header files
INCLUDES = -I.

MAIN_SRC = main.c trie.c
# Ensure the object file path is included for compilation
TEST_SRC = tests/trie_testing.c trie.c

MAIN_OBJ = $(MAIN_SRC:.c=.o)
# Specify the object file output path for the test source
TEST_OBJ = $(patsubst %.c,%.o,$(TEST_SRC))

MAIN_EXE = main_program
TEST_EXE = test_program

.PHONY: all clean main test

all: main test

main: $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN_EXE) $(MAIN_OBJ)

test: $(TEST_OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TEST_EXE) $(filter-out main.o, $(TEST_OBJ))

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(MAIN_OBJ) $(TEST_OBJ) $(MAIN_EXE) $(TEST_EXE) tests/*.o


