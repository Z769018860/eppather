LIB_NAME := Parser
STATIC_NAME := lib$(LIB_NAME).a
SHARE_NAME := lib$(LIB_NAME).so

INCL := -I./z3/api/
INCL1 := -I./z3/api/c++/
INCL2 := -I./bison/
LIB := -L./z3/bin/

g++ := g++-10
std := -std=c++20

# all : static_libaray shared_libaray

all : static_libaray

static_libaray:
	$(g++) $(std) -c *.cpp $(INCL) $(INCL1) $(INCL2) -finput-charset=utf-8
	ar -cr $(STATIC_NAME) *.o

shared_libaray:
	$(g++) $(std) -shared -fpic -o $(SHARED_NAME) *.cpp $(INCL) $(INCL1) $(INCL2) $(LIB) -lz3 -finput-charset=utf-8

clean:
	rm -rf *.o
	rm -rf *.a *.so