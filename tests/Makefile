OBJS =  Index.o ListNodePos.o ListNode.o Buffer.o Graph.o Check.o ListNodeCheck.o
HEADER = ../Index.h ../ListNodePos.h ../ListNode.h ../Buffer.h ../Graph.h

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

ListNodePos.o: ../ListNodePos.cpp
	$(CC) $(COMP_FLAGS) ../ListNodePos.cpp

ListNode.o: ../ListNode.cpp
	$(CC) $(COMP_FLAGS) ../ListNode.cpp

Buffer.o: ../Buffer.cpp
	$(CC) $(COMP_FLAGS) ../Buffer.cpp

Graph.o: ../Graph.cpp
	$(CC) $(COMP_FLAGS) ../Graph.cpp

ListNodeCheck.o: ListNodeCheck.cpp
	$(CC) $(COMP_FLAGS) ListNodeCheck.cpp

Check.o: Check.cpp
	$(CC) $(COMP_FLAGS) Check.cpp

clean:
	rm -f check $(OBJS)

