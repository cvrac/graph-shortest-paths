OBJS =  Index.o main.o
HEADER = Index.h

all: gsp

CC 	= g++
FLAGS	= -c

gsp: $(OBJS) $(HEADER)
	$(CC) -o gsp $(OBJS)

Index.o: Index.cpp
	$(CC) $(FLAGS) Index.cpp

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

clean:
	rm -f gsp $(OBJS)

