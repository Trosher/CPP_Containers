CFLAGS= -lstdc++ -std=c++17 -Wall -Werror -Wextra 
TEST= -lgtest test.cc
NAME_TEST=-o test
CC=gcc

all: clean test

test: clean
	$(CC) $(CFLAGS) $(TEST) $(NAME_TEST)
	./test

clean:
	rm -rf test