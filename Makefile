
all:
	clang++ -std=c++11 -stdlib=libc++ Sample.cpp -o Sample.app

clean:
	rm *.app

.PHONY: all clean
