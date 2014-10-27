
#include <memory>
#include <functional>
#include <iostream>

using namespace std;

///
///	Manage resources (pointers, textures, sounds) with Objects in C++.
/// That means: don't store raw pointers to things. Don't use new and delete.
///
/// Object destructors are automatically called in C++ when an Object falls out of scope.
/// If you manage resources with an Object, you can know that as long as the object exists,
/// the resource is in a known state.
///
/// Once the object ceases to exist, it can automatically clean up the resource in its destructor.
///
/// std::shared_ptr is an extremely useful Object that manages the lifetime of a pointer.
///

///
/// DummyObject prints to cout when it is created and destroyed.
/// It also updates a counter, so we can tally the total DummyObject's in existence.
///
class DummyObject
{
public:
	DummyObject( const std::string &name, const std::shared_ptr<int> &counter ):
		name( name ),
		counter( counter )
	{
		*counter += 1;
		cout << "Created " << name << endl;
	}

	~DummyObject()
	{
		*counter -= 1;
		cout << "Destroyed " << name << endl;
	}
private:
	string 								name;
	std::shared_ptr<int>	counter;
};

///
/// Test program showing destructor behavior.
///
int main( int argc, char const *argv[] )
{
	// Test counter.
	auto object_counter = make_shared<int>( 0 );

	{
		// Enter a new scope here so we can see object lifetime management

		// Creates an object that will live as long as it is in scope.
		// This is a reasonable default mode of creating things.
		DummyObject stack( "Stack Allocated", object_counter );

		// Creates a shared_ptr object that manages a pointer to a DummyObject object.
		// This is our default for objects that need to be created dynamically (e.g. for polymorphism)
		auto shared = make_shared<DummyObject>( "shared_ptr", object_counter );

		// Creates a unique_ptr object that manages a pointer to a DummyObject object.
		// When only one thing refers to a dynamically-created object, we use unique_ptr.
		auto unique = std::unique_ptr<DummyObject>( new DummyObject( "unique_ptr", object_counter ) );

		// unique_ptr can be converted to a shared_ptr.
		// We need to move() the unique_ptr object to avoid deleting the pointer in its destructor.
		// Once the unique_ptr object is moved(), it is no longer valid.
		auto unique_too = std::unique_ptr<DummyObject>( new DummyObject( "unique_ptr 2", object_counter ) );
		// Move the unique_ptr's contents into a shared_ptr.
		shared_ptr<DummyObject> shared_too = std::move( unique_too );

		// Creates and assign a raw pointer. Don't do this.
		// The raw pointer has no destructor, so it will
		// leak the DummyObject object once the pointer falls out of scope.
		DummyObject *raw = new DummyObject( "Raw Pointer", object_counter );

		cout << *object_counter << " element(s) created." << endl;
		cout << "===Leaving Scope===" << endl;
	}

	cout << *object_counter << " element(s) remaining." << endl;

	return 0;
}
