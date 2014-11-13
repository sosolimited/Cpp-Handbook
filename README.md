
# Effective Cpp Demos

Compilable source files explaining common modern C++ techniques. Heavily commented source files are meant to explain the content, while running the programs may show “proof” of their stated behavior.

Techniques shown are heavily inspired by Scott Meyer’s [Effective Cpp](http://www.aristeia.com/books.html) books as well as Herb Sutter’s [Guru of the Week](http://herbsutter.com/gotw/). Additionally, the content Bjarne Stroustrup’s [A Tour of C++](http://www.stroustrup.com/Tour.html) is essential.

We hope to cover enough of the content from those sources in a condensed format that makes it easy to jump in and be productive in a modern C++ project. Of course, we cannot cover the subject in as much depth or breadth as any of the sources mentioned above. Please see them if you are interested in more details.

More samples will be added over time, and some may be removed or heavily modified as we think of clearer ways to explain the concepts.

## Building
```bash
$ make all
```

## Running
```bash
$ ./SampleName.sample
```

## Current Samples:

The samples are loosely ordered. The sequence laid out below will hopefully make the most sense if you don't know where to start.

- Object Creation: creating C++ objects dynamically and on the stack.
- Namespaces and Aliases: organizing code into modules and writing readable names.
- Templates: creating functions that can operate on many types.
- Functional: creating function objects (lambdas).
- Collections: sequential and key-based containers, with "CRUD" operations on their contents.
- Async and Future: load and parse a file asynchronously and read the results back in the main thread.

## Early Samples
- Resource (Memory) Management: smart pointer types and managing resources (e.g. memory) with objects. Object Creation is probably a better sample for these concepts.

## Future Samples:
- Threads and atomics (for continuously-running objects that process tasks without returning a value)

## Code Style

This being a Sosolimited project, we follow the company code conventions throughout. We use 2-space tabs, so you might need to adjust your editor settings for everything to line up nicely.

## C++ Versions and Compatibility

This is only tested with clang on OSX. All code should work in VS2013, as well.

We tell the compiler to use C++14 so we can use std::make_unique, which (like many C++14 features) really just completes and adds consistency to things in C++11. Other than that, everything should compile fine with just C++11 (and much will with C++98).

Currently, C++14 is called C++1y by the command-line version of Clang on OSX. In Xcode, you can set your "C++ Language Dialect" to C++14. In your build settings, it will look like the following:
![C++ Language Dialect Screenshot](https://cloud.githubusercontent.com/assets/81553/5036817/f7f51060-6b50-11e4-8f81-9f41fbabc23c.png)
