FLAGS= -std=c++20 -O3
CXX=g++-13
MAKEFLAGS += --always-make
.PHONY: all

all: gen klevel-bf klevel-main

gen: gen.cc
	$(CXX) $^ -o $@ $(FLAGS)

klevel-bf: klevel-bf.cc
	$(CXX) $^ -o $@ $(FLAGS)

# need libboost
klevel-main: klevel-main.cc
	$(CXX) $^ -o $@ $(FLAGS) -I/opt/homebrew/Cellar/boost/1.84.0_1/include
