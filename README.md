
# Effective Cpp Demos

Compilable source files explaining common modern C++ techniques. Heavily commented source files are meant to explain the content, while running the programs may show “proof” of their stated behavior.

Techniques shown are heavily inspired by Scott Meyer’s [Effective Cpp](http://www.aristeia.com/books.html) books as well as Herb Sutter’s [Guru of the Week](http://herbsutter.com/gotw/). Additionally, the content Bjarne Stroustrup’s [A Tour of C++](http://www.stroustrup.com/Tour.html) is essential.

We hope to cover enough of the content from those sources in a condensed format that makes it easy to jump in and be productive in a modern C++ project. Of course, we cannot cover the subject in as much depth or breadth as any of the sources mentioned above. Please see them if you are interested in more details.

This is, as many things are, a work in progress.

## Building
```bash
$ make all
```

## Running
```bash
$ ./SampleName.sample
```

## Current Samples:
- Resource Management: smart pointer types and managing resources with objects.
- Namespaces and Aliases: covers ways of sectioning code with modules and writing readable names.
- Collections: covers different types of containers, with "CRUD" operations on their contents.

## Future Samples:
Concurrency (std::async, std::thread)

## Code Style

This being a Sosolimited project, we follow the company code conventions throughout. We use 2-space tabs, so you might need to adjust your editor settings for everything to line up nicely.
