
A Soso Tour of Modern C++
=========================

A high-level tour of C++ including compilable source files demonstrating common modern C++ concepts.

Heavily commented source files explain the concepts and show them in a practical format. Running the programs may show “proof” of their stated behavior.

These programs are not meant to exhaustively document what you can do with C++. Instead, they aim to show a subset of the language that is simple, productive, and--yes--even fun to work with.

Read through [The Tour](Cpp-Tour.md), and have a read through the source files. Build and run the sample applications. Try changing some code to see how it changes the program behavior.

## The Samples

The samples are loosely ordered. If you don't how what you want to look at, read through [The Tour](Cpp-Tour.md) and run the samples for the sections that need more clarification.

- __Object Creation__: creating C++ objects dynamically and on the stack.
- __Namespaces and Aliases__: organizing code into modules and writing readable names.
- __Templates__: creating functions that can operate on many types.
- __Functional__: creating function objects (lambdas).
- __Collections__: sequential and key-based containers, with "CRUD" operations on their contents.
- __Async and Future__: load and parse a file asynchronously and read the results back in the main thread.

### Building

```bash
$ make all
```

### Running

```bash
$ ./SampleName.sample
```

### Sample Layout

The samples are generally organized in four sections. First, there is a comment explaining what we will do in the sample. Second, we have the functions that do the work with additional detail in comments. Third, the main function calls the functions (sometimes, the second section just lives within the main function). Finally, any implementation details that aren't particularly relevant to the sample are defined after main().

## Code Style

This being a Sosolimited project, we follow the company code conventions throughout. We use 2-space tabs, so you might need to adjust your editor settings for everything to line up nicely.

View the [Soso C++ Style Guide](STYLE.md).

## C++ Versions and Compatibility

This is only tested with clang on OSX. All code should work in VS2013, as well.

We tell the compiler to use C++14 so we can use std::make_unique, which (like many C++14 features) really just completes and adds consistency to things in C++11. Other than that, everything should compile fine with just C++11 (and much will with C++98).

Currently, C++14 is called C++1y by the command-line version of Clang on OSX. That’s what we specify in our Makefile.

In Xcode, you can set your "C++ Language Dialect" to C++14. In your build settings, it will look like the following:

![C++ Language Dialect Screenshot](https://cloud.githubusercontent.com/assets/81553/5036817/f7f51060-6b50-11e4-8f81-9f41fbabc23c.png)
