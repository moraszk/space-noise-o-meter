.PHONY: clean all
	
clean:
	rm -rf parser_test

all: parser_test

parser_test: parser_test.cpp
	clang++ -I ../sw/Inc -o $@ $< --std=c++20 -g3
