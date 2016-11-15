OBJS =   ArrayTest.o
HEADER =  ../Garray.hpp

all: check

GTEST_INCLUDE = ~/googletest/googletest/include
GTEST_LIBDIR = ~/googletest/googletest/make
CC 	= g++
COMP_FLAGS	= -c -I $(GTEST_INCLUDE)
LINK_FLAGS  = -L $(GTEST_LIBDIR) -l gtest_main -lpthread

check: $(OBJS) $(HEADER)
	$(CC) $(OBJS) $(LINK_FLAGS) -o check

NodeIndex.o: ../NodeIndex.cpp
	$(CC) $(COMP_FLAGS) ../NodeIndex.cpp

ListNode.o: ../ListNode.cpp
	$(CC) $(COMP_FLAGS) ../ListNode.cpp

Buffer.o: ../Buffer.cpp
	$(CC) $(COMP_FLAGS) ../Buffer.cpp

Graph.o: ../Graph.cpp
	$(CC) $(COMP_FLAGS) ../Graph.cpp

ListNodeCheck.o: ListNodeCheck.cpp
	$(CC) $(COMP_FLAGS) ListNodeCheck.cpp

NodeIndexCheck.o: NodeIndexCheck.cpp
	$(CC) $(COMP_FLAGS) NodeIndexCheck.cpp

BufferCheck.o: BufferCheck.cpp
	$(CC) $(COMP_FLAGS) BufferCheck.cpp

HashTableCheck.o: HashTableCheck.cpp
	$(CC) $(COMP_FLAGS) HashTableCheck.cpp

HashTable.o: ../HashTable.cpp
	$(CC) $(COMP_FLAGS) ../HashTable.cpp

Queue.o: ../Queue.cpp
	$(CC) $(COMP_FLAGS) ../Queue.cpp

QueueCheck.o: QueueCheck.cpp
	$(CC) $(COMP_FLAGS) QueueCheck.cpp

Check.o: Check.cpp
	$(CC) $(COMP_FLAGS) Check.cpp

ArrayTest.o: ArrayTest.cpp
	$(CC) $(COMP_FLAGS) ArrayTest.cpp

clean:
	rm -f check $(OBJS)
