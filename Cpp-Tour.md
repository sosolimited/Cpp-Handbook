A Soso Tour of Cpp
==================

This document outlines some core C++ concepts from a high level. Compilable source files demonstrating the concepts accompany each category, and can be built using the instructions in the [Readme](README.md).

**Table of Contents**
- [Object Creation](#user-content-object-creation)
- [Namespaces and Aliases](#user-content-namespaces-and-aliases)
- [Templates](#user-content-templates)
- [Functional Programming](#user-content-functional-programming)
- [Collections](#user-content-collections)
- [Asynchronous Programming](#user-content-asynchronous-programming)

Object Creation
---------------
[Compilable Source](ObjectCreation.cpp?ts=2)

Objects can live in two main places: on the stack, or in dynamic memory. Objects that live on the stack are destroyed automatically when their name falls out of scope. Dynamic objects will live forever if unmanaged, so we use stack-allocated pointer objects to manage their lifetime.

### Stack Objects

Objects that live on the stack are declared simply by type and name. They live for as long as the scope in which they are declared. That could be the body of a function, the lifetime of the parent class instance, or the block of a for-loop.

Stack allocation is the preferred way to store your variables as it is simple and does the right thing. It looks like the following:

```c++
Object  object;
int     number = 5;
auto    value = 20.0f;
```

### Dynamic Objects

Dynamic allocation is useful when you want to share a single object between multiple users and for handling polymorphism. When memory is allocated dynamically, you receive a pointer to that memory. Since we want to control how long that memory lives, we manage the pointer with a pointer object that lives on the stack.

C++ provides two particularly useful pointer objects: std::shared_ptr and std::unique_ptr.
They are created with the std::make_shared and std::make_unique functions, respectively.

When we create managed dynamic objects, we are really creating two objects:
(1) the pointer object on the stack, and
(2) the pointed-to object in dynamic memory.

The pointer object is used as a handle (or pointer) to the dynamic object, and
automatically manages the memory (de)allocation of the dynamic object.

Creating pointer objects looks like the following:

```c++
std::shared_ptr<Object> objectRef = std::make_shared<Object>();
std::shared_ptr<Object> derivedRef = std::make_shared<DerivedType>();
std::unique_ptr<Object> objectURef = std::make_unique<Object>();
```

Generally, we will want to get the type information from the right side of our assignment (rather than describe it twice). The following code produces identical results to the above:

```c++
auto objectRef = std::make_shared<Object>();
auto derivedRef = std::shared_ptr<Object>( std::make_shared<DerivedType>() );
auto objectURef = std::make_unique<Object>();
```

Since the dynamic memory `Object` in the above code is managed by a stack-allocated pointer object, we know the dynamic memory will be freed when our pointer object falls out of scope.


Namespaces and Aliases
----------------------
[Compilable Source](NamespacesAndAliases.cpp?ts=2)

When dealing with large projects or multiple sets of code, it is useful to group sections of code together under a common name. Similarly, it can be useful to have a shorthand for complex types.

### Namespaces

Namespaces allow us to group sections of code together and write natural names for the types within each section.

In general, we declare a namespace for the project we are working on. This helps prevent naming conflicts between different sections of our code. It also makes it clear where different pieces of functionality are coming from when refactoring and debugging.

We declare namespaces like so:

```c++
namespace project {

  void function();

} // namespace project
```

And access members in the namespace as follows:

In a header file:
```c++
project::function();
```

In an implementation file (.cpp):
```c++
using namespace project;

function();

```

### Aliases

Aliases allow us to derive clear names from verbose types where needed. Often, you can use `auto` to capture a verbose type. However, when you need to store the type as a class member or receive it as a function parameter, aliases can help keep things legible.

When declaring aliases, make sure you are inside your own namespace or in an implementation file to avoid naming conflicts elsewhere.

We write aliases as follows:

```c++
using ObjectRef = std::shared_ptr<Object>;
using Callback = std::function<void (float, const std::string &)>;

// Templates can be aliased, too:
template<typename T> using Handle = std::shared_ptr<T>;
using ThingHandle = Handle<Thing>;
```


Templates
---------
[Compilable Source](Templates.cpp?ts=2)

Templates allow us to write code that can operate on any type. They enable compile-time polymorphism: the template is filled out by the compiler for each type that uses it.

While you may not write many templates in day-to-day programming, you will use them whenever you create a dynamically allocated object with make_shared or store objects in an STL container.

Template functions and types do their best to derive their type from the parameters you pass to them or their constructors. Sometimes, however, the compiler can't effectively deduce all the template types from the parameters received. In those cases, you must help the compiler along by filling in the template parameters yourself.

When needed, template parameters are passed in using angle-brackets:

```c++
std::vector<Object> collection;
std::shared_ptr<Object> reference;
auto result = std::max<float>( 10, 20.0 );
```

Functional Programming
----------------------
[Compilable Source](Functional.cpp?ts=2)

### Function Objects (std::function)

C++ has a lot of things that can behave like a function. Fortunately, it also has a function object that can refer to any of them.

`std::function<>` is a template that receives a function signature as its parameters. Function objects created by filling out the template can refer to any callable type that matches the signature.

Some possible function object declarations:

```c++
std::function<void ()>        void_fn;
std::function<float (float)>  lerp_fn;
```

When a function object doesn't refer to a function, testing it like a boolean returns false. Make sure you have a function to call from your function object before using it.

```c++
if( void_fn ) {
  void_fn();
}

if( lerp_fn ) {
  auto result = lerp_fn( 5.0f );
}
```

### Lambdas (\[] () {})

Lambda expressions produce function objects.

Lambdas are closely related to functions. Functions receive parameters when they are called; Lambdas receive set of parameters when you create them, and return a function.

Lambda syntax varies a bit from other functions. It begins with the capture block `[]` which is where you pass parameters to the lambda. Following that is the familiar `()` of a function, where you declare the parameters that the resulting function will receive. Finally, the familiar function block `{}` contains the code the function will run.

```c++
std::function<void ()> fn = [] () {};
```

In general, the compiler can deduce the return type based on what you write inside the function body. In the cases where it can't, you can write the return type using the trailing return style:

```c++
auto fn = [] () -> string { return someOtherFunction(); };
```

Parameters passed to the lambda take the same form as parameters passed to a function. If named in the argument block, parameters will be passed by value. If preceded by an ampersand, they will be passed by reference.

```c++
int i = 5;
int j = 0;
// Capture i by value and j by reference.
// i will always have the same value in our lambda.
auto fn = [i, &j] () {
  j += i;
};

i = 0;  // doesn't affect fn's i, since we captured by value.
fn();   // j now equals 5, since variable is referenced in fn.
```

Collections
-----------
[Compilable Source](Collections.cpp?ts=2)

C++ provides a large number of container types in the STL.

The container interface is very similar across types, though certain containers only implement parts of the interface.

Some common methods include:
- `size()`  - returns how many elements the collection contains.
- `empty()` - returns true if the collection is empty.
- `clear()` - removes everything from the collection.
- `erase()` - removes a range of elements from the collection.
- `assign()` - replace the contents of the collection with an element or range.
- `insert()` - add an element or range to the collection at a specified position.
- `at()` - returns the element at the specified index or key.

### Sequential Containers

#### Vector
`std::vector<Type>`

Vectors are the go-to sequential container. They can store a variable number of elements and provide fast iteration and index-based lookup.

Vectors store their contents in a contiguous block of memory and resize themselves as needed. When a vector is resized, it copies the old contents to a new block of memory.

Due to the way it is laid out, we typically only modify the end of a vector.

```c++
vector<float> numbers;
numbers.push_back( 10.0f );
numbers.push_back( 0.5f );
```

#### Array
`std::array<Type, Size>`

Arrays store a fixed number of elements. In contrast to a C array, C++’s array type knows how long it is.

```c++
std::array<float, 5> array;
array.at( 4 ) = 10.0f;
```

#### List
`std::list<Type>`

If you frequently need to modify the front of a container, consider using a std::list. It is implemented as a doubly-linked-list, which makes it cheap to change at arbitrary positions, but it is comparatively slow for iteration and index-based lookup compared to std::vector.

### Associative Containers

Associative containers let you look up contents by a key other than their index (and may not have an index). The data is associated with a key of your choosing.

Common methods:
- `count()` - returns the number of times the key appears in the collection. (0 or 1 for the containers we use.)
- `find()` - returns the iterator for the key/value pair in the collection. (collection::end() if not found)

#### Map
`std::map<Key, Value>`

A map stores key-value pairs, allowing you to look up contents by a key other than an index. Maps are stored as a tree structure.

```c++
std::map<std::string, float> numbers;
numbers["five"] = 5.0f;
numbers.insert( make_pair( "ten", 10.0f ) );

float val = numbers.at( "five" );
```

#### Unordered Map
`std::unordered_map<Key, Value>`

An unordered_map is a map structure that is implemented using a hash table. With large collections, it will generally be faster to look up elements in an unordered_map than a map.

You use unordered_maps the same way you use maps.

#### Set
`std::set<Key>`

A set is a collection that guarantees each value it contains will only be stored once. They are useful for keeping track of things like selections a user made or possible next moves in a game.

Asynchronous Programming
------------------------

There are many approaches to and reasons for asynchronous programming. Generally, we use asynchronous handling when we want to get some big chunk of work done, but need to keep our animations running smoothly and UI responsive while it happens.

### Futures
[Compilable Source](AsyncAndFuture.cpp?ts=2)

`std::async` runs a function in parallel with your current code. It returns a `future` that you can use to check on the progress of the function.

In addition to letting you check whether your asynchronous function has completed, futures let you get the return value of the function when it is complete.

```c++
// Create a function that will do the work we want.
auto load_and_parse_file = [path] () {
  // pretend this does something...
  return file_contents;
};

// Run our function asynchronously.
future<Contents> data = std::async( std::launch::async, load_and_parse_file );

// Time passes as we do something else...

// Check in on our data.
if( data.valid() ) {
  auto status = data.wait_for( 1ns );
  // If we are all done here,
  if( status == std::future_status::ready ) {
    // Use our data.
    Contents c = data.get();
  }
}
```

Note that you must store the future returned by std::async if you want the code to actually run asynchronously. This is true even if you don't care about the return value.

### Threads

C++11 provides a std::thread object that executes a function in parallel to the main thread. If you want to have a continuously running process with minimal communication back to the main thread, it can make sense to use a thread.

If you want to do some work in parallel to your main thread and get the result back, it usually makes more sense to use a std::future.

```c++
std::thread t;
t = std::thread( some_function );
```

If you want to share data between threads, you must protect it with a mutex wherever it is used to avoid race conditions.

```c++
std::mutex dataMutex;
DataType   data;

// Returns a copy of data.
// Lock to make sure data doesn't change during copy.
DataType getData() {
  std::lock_guard lock( dataMutex );
  return data;
}

// Change a member of data.
// Lock to make sure nothing else changes data until after we finish.
void changeDataMember( float iA ) {
  std::lock_guard lock( dataMutex );
  data.a = iA;
}
```

Threads can be useful, but if you are returning data from a parallel process, try using std::async first. Not only do futures reduce the chances for race conditions, they also enable you to control the re-entry point for asynchronous code.
