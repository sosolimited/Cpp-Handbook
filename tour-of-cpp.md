A Soso Tour of Cpp
==================

This document outlines some core C++ concepts from a high level. Compilable source files demonstrating the concepts accompany each category, and can be built using the instructions below.

This is not meant to exhaustively document what you can do with C++. Instead, we aim to show a subset of the language that is simple, productive, and--yes--even fun to work with.

**Table of Contents**
- [Building the Samples](#user-content-working-with-the-samples)
- [Object Creation](#user-content-object-creation)
- [Parameter Passing](#user-content-parameter-passing)
- [Types and Polymorphism](#user-content-types-and-polymorphism)
- [Namespaces and Aliases](#user-content-namespaces-and-aliases)
- [Templates](#user-content-templates)
- [Functional Programming](#user-content-functional-programming)
- [Collections](#user-content-collections)
- [Asynchronous Programming](#user-content-asynchronous-programming)
- [Next Steps](#user-content-where-to-go-from-here)

Working with the Samples
------------------------

### Building and Running

The samples are built with a simple Makefile. So far, they have only been tested with clang on OSX. All code should work in VS2013 and with recent versions of gcc, as well.

```bash
# Build all samples
$ cd samples
$ make all

# Run a sample
$ ./SampleName.sample
```

### A Note on Language Versions

We tell the compiler to use C++14 so we can use std::make_unique, which (like many C++14 features) completes and adds consistency to features in C++11. We specify the C++ version we want by passing an option to the compiler in the Makefile.

In Xcode, you can set your “C++ Language Dialect” to C++14. In your build settings, it will look like the following:

![C++ Language Dialect Screenshot](https://cloud.githubusercontent.com/assets/81553/5036817/f7f51060-6b50-11e4-8f81-9f41fbabc23c.png)

### Sample Code Layout

The samples are generally organized in four sections. First, there is a comment explaining what the sample does. Second, we have the code that does the work. Third, the main function calls the functions to do work (sometimes, the second section just lives within the main function). Finally, we try to define any implementation details that aren't particularly relevant to the sample after main().

Object Creation
---------------
[Compilable Source](samples/ObjectCreation.cpp?ts=2)

Objects can live in two main places: on the stack, or in dynamic memory. Objects that live on the stack are destroyed automatically when their name falls out of scope. Dynamic objects will live forever if unmanaged, so we use stack-allocated pointer objects to manage their lifetime.

### Stack Objects

Objects that live on the stack are declared simply by type and name. They live for as long as the scope in which they are declared. That scope could be the body of a function, the lifetime of the parent class instance, or the block of a for-loop.

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

Parameter Passing
-----------------

There are three basic rules for passing parameters

- Pass built-in types by value (float, double, int).
- Pass read-only parameters by const T&.
- Pass read-write parameters by T&.

In code, this ends up looking like the following:

```c++
float passByValue( float iValue );
void useObjectInfo( const Type &iObject );
void modifyObject( Type &iObject );

float number = 10.0f;
number = passByValue( number );

Type instance;
shared_ptr<Type> dynamicInstance;

useObjectInfo( instance );
useObjectInfo( *dynamicInstance );

modifyObject( instance );
modifyObject( *dynamicInstance );
```

With the introduction of move-only types in C++11, we get a fourth rule that only occasionally comes into effect:

- When you have a move-only type that you want to pass ownership of to a new name, pass by T&&.

This occurs most commonly when you want to pass ownership of a std::unique_ptr (or an object that has a std::unique_ptr as a member) into a function. In that case you move the unique_ptr into the function, explicitly giving up control over the pointed-to object.

```c++
void takeOwnershipOfPointer( std::unique_ptr<Type> &&iPtr );

unique_ptr<Type> ptr;
takeOwnershipOfPointer( std::move( ptr ) );
```

There is currently some debate around whether it is preferable to pass by T or T&& when passing a move-only type to a function that will take ownership of the object. T&& makes it clear that the caller should no longer own the object, and it makes sure the object is only moved once.

Types and Polymorphism
----------------------

C++ provides a large number of built-in data types. You can also create your own data types as structs or classes.

### Structs

Structs are useful for holding plain old data. Their members are public by default.

```c++
// Data holds a number of pieces of public data.
struct Data {
  int         member;
  int         another;
  std::string name;
};
```

### Classes

Classes are used when objects should have more functionality than simply holding data. Their members are private by default.

Data in a class can be given a default initial value in the declaration. For built-in numeric types, we provide default values in order to avoid bugs from uninitialized data.

```c++
// Create a class named Type.
class Type {
public:
  void doSomething();

private:
  // Data members are declared private.
  int   someMember = 10;
  float another = 5.0f;
};

// Create an object of type Type.
Type thing;
```

### Inheritance

Classes and structs can inherit from other classes. Base classes should have a virtual destructor. Any methods that the derived class can override must be marked as `virtual` in the base class and with `override` in the derived class.

```c++
// Base class has some virtual methods, and a virtual destructor.
class Base {
public:
  // Mark destructor as virtual so derived destructors get called.
  virtual ~Base() = default;
  // draw() can be overridden since it is virtual.
  virtual void draw() const;
  // doSomething() cannot be overriden, since it is not virtual.
  void doSomething();
};

// Derived inherits the public interface from Base
class Derived : public Base {
public:
  // virtual method that is overridden is marked with override.
  void draw() const override;
};
```

Namespaces and Aliases
----------------------
[Compilable Source](samples/NamespacesAndAliases.cpp?ts=2)

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

In a header file (.h):
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
[Compilable Source](samples/Templates.cpp?ts=2)

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
[Compilable Source](samples/Functional.cpp?ts=2)

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

Lambdas are closely related to functions. Functions receive parameters when they are called; Lambdas receive parameters when you create them, and return a function.

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
[Compilable Source](samples/Collections.cpp?ts=2)

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

C++ constructs for enabling asynchronous programming include `async` calls with `futures`, and `threads` with `atomics` and `mutexes`. Futures and async not only reduce the chances for race conditions, they also enable you to control the re-entry point for asynchronous code. Threads are useful for continuously-running functions, and especially when you don't need results from the function back on the main thread.

### Async and Future
[Compilable Source](samples/AsyncAndFuture.cpp?ts=2)

`std::async` runs a function in parallel with your current code. It returns a `future` that you can use to check on the progress of the function.

In addition to letting you check whether your asynchronous function has completed, futures let you get the return value of the function when it is complete.

```c++
// Run a function asynchronously.
std::future<string> data = std::async( std::launch::async, some_function );

// Time passes as we do something else...

// Check in on our data.
if( data.valid() ) {
  auto status = data.wait_for( 1ns );
  // If we are all done here,
  if( status == std::future_status::ready ) {
    // Use our data.
    string c = data.get();
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

If you want to share data between threads, you need to synchronize it using some means. C++ provides two options for synchronizing data: the `std::atomic<>` template and `std::mutex`.

#### Atomic

Atomic operations cannot be divided into multiple steps, which makes them safe to use across multiple threads. The std::atomic template wraps a piece of data so that operations on that data are atomic.

```c++
std::atomic<float> sharedData;
```

#### Mutex

Mutexes can be used to protect data as well. Only one thread can lock a mutex at a time, so content correctly protected by a mutex can be safe to share between threads.

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

Where to go from here
---------------------

The concepts shown above and in the sample code are informed by Scott Meyer’s [Effective Cpp](http://www.aristeia.com/books.html) books as well as Herb Sutter’s [Guru of the Week](http://herbsutter.com/gotw/) column. Additionally, Bjarne Stroustrup’s recent [A Tour of C++](http://www.stroustrup.com/Tour.html) was influential in setting the tone of the samples. If you are interested in learning more in breadth and/or depth, have a look at those sources.

For more breadth and depth, start here:
- [A Tour of C++](http://www.stroustrup.com/Tour.html)
- [Guru of the Week](http://herbsutter.com/gotw/)
- [Effective Modern C++](http://shop.oreilly.com/product/0636920033707.do)

For detailed reference materials, start here:
- [MSDN C++ Reference](http://msdn.microsoft.com/en-us/library/3bstk3k5.aspx)
- [MSDN C++ Standard Library Reference](http://msdn.microsoft.com/en-us/library/cscc687y.aspx)
- [cplusplus.com](http://www.cplusplus.com/reference/)
- [cppreference.com](http://en.cppreference.com/w/)
