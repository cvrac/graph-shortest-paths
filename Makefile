OBJS =  NodeIndex.o ListNode.o HashTable.o ShortestPath.o Buffer.o Graph.o OperationsControl.o main.o Array.o
HEADER = NodeIndex.hpp ListNode.hpp HashTable.hpp ShortestPath.hpp Buffer.hpp Graph.hpp OperationsControl.hpp Array.hpp Garray.hpp

all: gsp

CC 	= g++
FLAGS	= -O2 -c

gsp: $(OBJS) $(HEADER)
	$(CC) -O2 -o gsp $(OBJS)

Array.o: Array.cpp
	$(CC) $(FLAGS) Array.cpp

NodeIndex.o: NodeIndex.cpp
	$(CC) $(FLAGS) NodeIndex.cpp

ListNode.o: ListNode.cpp
	$(CC) $(FLAGS) ListNode.cpp

HashTable.o: HashTable.cpp
	$(CC) $(FLAGS) HashTable.cpp

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
	wc -l *.cpp $(HEADER)
