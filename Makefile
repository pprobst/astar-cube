CC = g++
CFLAGS = -Wall -std=c++14
NAME = astar

all:
	$(CC) $(CFLAGS) -o $(NAME) *.cpp

clean:
	rm $(NAME)
