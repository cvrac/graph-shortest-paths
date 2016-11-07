OBJS =  Index.o ListNode.o HashTable.o PathEntry.o ShortestPath.o Buffer.o Graph.o OperationsControl.o main.o Queue.o
HEADER = Index.h ListNodePos.h ListNode.h HashTable.h PathEntry.h ShortestPath.h Buffer.h Graph.h OperationsControl.h Queue.h

all: gsp

CC 	= g++
FLAGS	= -O2 -c

gsp: $(OBJS) $(HEADER)
	$(CC) -O2 -o gsp $(OBJS)

Queue.o: Queue.cpp
	$(CC) $(FLAGS) Queue.cpp

Index.o: Index.cpp
	$(CC) $(FLAGS) Index.cpp

ListNode.o: ListNode.cpp
	$(CC) $(FLAGS) ListNode.cpp

HashTable.o: HashTable.cpp
	$(CC) $(FLAGS) HashTable.cpp

PathEntry.o: PathEntry.cpp
	$(CC) $(FLAGS) PathEntry.cpp

ShortestPath.o: ShortestPath.cpp
	$(CC) $(FLAGS) ShortestPath.cpp

Buffer.o: Buffer.cpp
	$(CC) $(FLAGS) Buffer.cpp

Graph.o: Graph.cpp
	$(CC) $(FLAGS) Graph.cpp

OperationsControl.o: OperationsControl.cpp
	$(CC) $(FLAGS) OperationsControl.cpp

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

clean:
	rm -f gsp $(OBJS)

count:
	wc -l *.cpp *.h
