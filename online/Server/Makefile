	PROG=bin/mcserver
	OBJS=source/mcserver.cpp source/gui.cpp source/chess.cpp
	CC=g++
	LIBS=-lncurses -lpthread

all: $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LIBS)

clean:
	rm -rf source/*.o
