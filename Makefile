OBJS =  NodeIndex.o ListNode.o ShortestPath.o Buffer.o Graph.o OperationsControl.o main.o SCC.o CC.o GrailIndex.o
HEADER = src/NodeIndex.hpp src/ListNode.hpp src/HashTable.hpp src/SCC.hpp src/ShortestPath.hpp src/Buffer.hpp src/Graph.hpp src/OperationsControl.hpp src/Garray.hpp src/CC.hpp src/GrailIndex.hpp

all: gsp

CC 	= g++
FLAGS	= -O2 -c

gsp: $(OBJS) $(HEADER)
	$(CC) -O2 -o gsp $(OBJS)

Array.o: src/Array.cpp
	$(CC) $(FLAGS) src/Array.cpp

NodeIndex.o: src/NodeIndex.cpp
	$(CC) $(FLAGS) src/NodeIndex.cpp

ListNode.o: src/ListNode.cpp
	$(CC) $(FLAGS) src/ListNode.cpp

GrailIndex.o: src/GrailIndex.cpp
	$(CC) $(FLAGS) src/GrailIndex.cpp

SCC.o: src/SCC.cpp
	$(CC) $(FLAGS) src/SCC.cpp

CC.o: src/CC.cpp
	$(CC) $(FLAGS) src/CC.cpp

ShortestPath.o: src/ShortestPath.cpp
	$(CC) $(FLAGS) src/ShortestPath.cpp

Buffer.o: src/Buffer.cpp
	$(CC) $(FLAGS) src/Buffer.cpp

Graph.o: src/Graph.cpp
	$(CC) $(FLAGS) src/Graph.cpp

OperationsControl.o: src/OperationsControl.cpp
	$(CC) $(FLAGS) src/OperationsControl.cpp

main.o: src/main.cpp
	$(CC) $(FLAGS) src/main.cpp

clean:
	rm -f gsp $(OBJS)

count:
	wc -l *.cpp $(HEADER)
