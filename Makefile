CXX=clang++
CXXFLAGS=-O3 -Werror -Weverything -Wpedantic -Wno-c++98-compat -std=c++14

all: test_kleisli

clean:
	rm -f test_kleisli
