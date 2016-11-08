OBJS =  Index.o ListNode.o Buffer.o Graph.o Check.o ListNodeCheck.o IndexCheck.o BufferCheck.o
HEADER = ../Index.hpp ../ListNodePos.hpp ../ListNode.hpp ../Buffer.hpp ../Graph.hpp

all: check

GTEST_INCLUDE = ~/googletest-master/googletest/include
GTEST_LIBDIR = ~/googletest-master/googletest/make
CC 	= g++
COMP_FLAGS	= -c -I $(GTEST_INCLUDE)
LINK_FLAGS  = -L $(GTEST_LIBDIR) -l gtest_main -lpthread

check: $(OBJS) $(HEADER)
	$(CC) $(OBJS) $(LINK_FLAGS) -o check

Index.o: ../Index.cpp
	$(CC) $(COMP_FLAGS) ../Index.cpp

ListNode.o: ../ListNode.cpp
	$(CC) $(COMP_FLAGS) ../ListNode.cpp

Buffer.o: ../Buffer.cpp
	$(CC) $(COMP_FLAGS) ../Buffer.cpp

Graph.o: ../Graph.cpp
	$(CC) $(COMP_FLAGS) ../Graph.cpp

ListNodeCheck.o: ListNodeCheck.cpp
	$(CC) $(COMP_FLAGS) ListNodeCheck.cpp

IndexCheck.o: IndexCheck.cpp
	$(CC) $(COMP_FLAGS) IndexCheck.cpp

BufferCheck.o: BufferCheck.cpp
	$(CC) $(COMP_FLAGS) BufferCheck.cpp

Check.o: Check.cpp
	$(CC) $(COMP_FLAGS) Check.cpp

clean:
	rm -f check $(OBJS)

