FLAGS := -std=c++11 -stdlib=libc++
CPP_FILES := $(wildcard *.cpp)
SAMPLES := $(CPP_FILES:.cpp=.sample)

# Create .sample files from .cpp files
# $^ is the right-hand-side item, $@ is the left-hand-side item.
%.sample:%.cpp
	clang++ $(FLAGS) $^ -o $@

all: $(SAMPLES)

clean:
	rm *.sample

.PHONY: all clean
