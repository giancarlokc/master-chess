	PROG=bin/mcclient
	OBJS=source/mcclient.cpp source/gui.cpp source/chess.cpp
	CC=g++
	LIBS=-lncurses -lpthread

all: $(OBJS)
	$(CC) -o $(PROG) $(OBJS) $(LIBS)

clean:
	rm -rf source/*.o
