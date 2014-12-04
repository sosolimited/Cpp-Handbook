A Soso Tour of Cpp
==================

This document outlines some core C++ concepts from a high level. Compilable source files demonstrating the concepts accompany each category, and can be built using the instructions in the [Readme](README.md).

**Table of Contents**
- [Object Creation](#)
- [Namespaces and Aliases](#)
- [Templates](#)
- [Functional Programming (Lambdas)](#)
- [Collections](#)
	- [Sequential Containers](#)
	- [Associative Containers](#)
- [Asynchronous Programming](#)
	- [Futures](#)
	- [Threads](#)

Object Creation
---------------
[Compilable Source](ObjectCreation.cpp?ts=2)

Namespaces and Aliases
----------------------
[Compilable Source](NamespacesAndAliases.cpp?ts=2)

Templates
---------
[Compilable Source](Templates.cpp?ts=2)

Functional Programming (Lambdas)
--------------------------------
[Compilable Source](Functional.cpp?ts=2)

Collections
-----------
[Compilable Source](Collections.cpp?ts=2)

C++ provides a large number of container types in the STL.

### Sequential Containers

`std::vector<Type>`
`std::array<Type, Size>`
`std::list<Type>`

### Associative Containers

`std::map<Key, Value>`

Asynchronous Programming
------------------------

### Futures
[Compilable Source](AsyncAndFuture.cpp?ts=2)

`std::future<Type>` will eventually hold a value of type Type. When it is ready, you can access the value.

Futures are returned from calls to std::async.

### Threads