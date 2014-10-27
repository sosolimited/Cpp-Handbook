FLAGS := -std=c++11 -stdlib=libc++
CPP_FILES := $(wildcard *.cpp)
SAMPLES := $(CPP_FILES:.cpp=.sample)

# Create .sample files from .cpp files.
# $^ is the right-hand-side item, $@ is the left-hand-side item.
# $< is the first right-hand-side item.
# wildcard makes the header dependency optional.
%.sample:%.cpp $(wildcard %.h)
	clang++ $(FLAGS) $< -o $@

all: $(SAMPLES)

clean:
	rm *.sample

.PHONY: all clean
