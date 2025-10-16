LLVM_CONFIG ?= llvm-config

CXX := clang++
CXXFLAGS := $(shell $(LLVM_CONFIG) --cxxflags) -fPIC -fno-rtti -std=c++17
LDFLAGS := $(shell $(LLVM_CONFIG) --ldflags)
# 仅包含必需的LLVM库，排除Polly
LLVM_LIBS := $(shell $(LLVM_CONFIG) --libs core irreader bitwriter) $(shell $(LLVM_CONFIG) --system-libs | sed 's/-lzstd//')

all: arrayAccessPass.so

arrayAccessPass.so: ArrayAccessCounter.o
	$(CXX) -shared $^ -o $@ $(LDFLAGS) $(LLVM_LIBS)

ArrayAccessCounter.o: ArrayAccessCounter.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f *.o *.so
