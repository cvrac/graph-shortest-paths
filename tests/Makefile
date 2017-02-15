OBJS =   ArrayTest.o ListNodeCheck.o NodeIndexCheck.o BufferCheck.o HashTableCheck.o ListNode.o NodeIndex.o Buffer.o
HEADER =  ../src/Garray.hpp

all: check

GTEST_INCLUDE = googletest/googletest/include
GTEST_LIBDIR = googletest/googletest/make
CC 	= g++
COMP_FLAGS	= -c -I $(GTEST_INCLUDE)
LINK_FLAGS  = -L $(GTEST_LIBDIR) -l gtest_main -lpthread

check: $(OBJS) $(HEADER)
	$(CC) $(OBJS) $(LINK_FLAGS) -o check

NodeIndex.o: ../src/NodeIndex.cpp
	$(CC) $(COMP_FLAGS) ../src/NodeIndex.cpp

ListNode.o: ../src/ListNode.cpp
	$(CC) $(COMP_FLAGS) ../src/ListNode.cpp

Buffer.o: ../src/Buffer.cpp
	$(CC) $(COMP_FLAGS) ../src/Buffer.cpp

Graph.o: ../src/Graph.cpp
	$(CC) $(COMP_FLAGS) ../src/Graph.cpp

ListNodeCheck.o: ListNodeCheck.cpp
	$(CC) $(COMP_FLAGS) ListNodeCheck.cpp

NodeIndexCheck.o: NodeIndexCheck.cpp
	$(CC) $(COMP_FLAGS) NodeIndexCheck.cpp

BufferCheck.o: BufferCheck.cpp
	$(CC) $(COMP_FLAGS) BufferCheck.cpp

HashTableCheck.o: HashTableCheck.cpp
	$(CC) $(COMP_FLAGS) HashTableCheck.cpp

Check.o: Check.cpp
	$(CC) $(COMP_FLAGS) Check.cpp

ArrayTest.o: ArrayTest.cpp
	$(CC) $(COMP_FLAGS) ArrayTest.cpp

clean:
	rm -f check $(OBJS)
