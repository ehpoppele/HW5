CXX = g++
CCFLAGS = -O3 -Wall -Wextra -pedantic -Werror

all: test_tree 

test_tree: test_tree.cc
	$(CXX) $(CCFLAGS) test_tree.cc -o test_tree

clean :
	rm test_tree.o