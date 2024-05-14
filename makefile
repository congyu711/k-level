FLAGS := -std=c++20 -O3
OS := $(shell uname -s)
ifeq ($(OS),Darwin)
	BOOSTINC := -I/opt/homebrew/include
	CXX := g++-14
else
	# BOOSTINC := -I/usr/include
	CXX := g++
endif
MAKEFLAGS += --always-make
.PHONY: all

all: gen klevel-bf klevel-main

gen: gen.cc
	$(CXX) $^ -o $@ $(FLAGS)

klevel-bf: klevel-bf.cc
	$(CXX) $^ -o $@ $(FLAGS)

# need libboost
klevel-main: klevel-main.cc
	$(CXX) $^ -o $@ $(FLAGS) $(BOOSTINC)
