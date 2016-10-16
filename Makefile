OBJS =  Index.o ListNodePos.o ListNode.o Buffer.o Graph.o main.o
HEADER = Index.h

all: gsp

CC 	= g++
FLAGS	= -c

gsp: $(OBJS) $(HEADER)
	$(CC) -o gsp $(OBJS)

Index.o: Index.cpp
	$(CC) $(FLAGS) Index.cpp

ListNodePos.o: ListNodePos.cpp
	$(CC) $(FLAGS) ListNodePos.cpp

ListNode.o: ListNode.cpp
	$(CC) $(FLAGS) ListNode.cpp

Buffer.o: Buffer.cpp
	$(CC) $(FLAGS) Buffer.cpp

Graph.o: Graph.cpp
	$(CC) $(FLAGS) Graph.cpp

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

clean:
	rm -f gsp $(OBJS)

