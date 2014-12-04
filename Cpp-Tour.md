A Soso Tour of Cpp
==================


Object Creation
---------------
[Source](ObjectCreation.cpp)

Namespaces and Aliases
----------------------
[Source](NamespacesAndAliases.cpp?ts=2)

Templates
---------
[Source](Templates.cpp)

Functional Programming (Lambdas)
--------------------------------
[Source](Functional.cpp)

Collections
-----------
[Source](Collections.cpp)

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
[Source](AsyncAndFuture.cpp)

`std::future<Type>` will eventually hold a value of type Type. When it is ready, you can access the value.

Futures are returned from calls to std::async.

### Threads