
#include <memory>
#include <functional>
#include <iostream>

using namespace std;

///
/// Objects can be created in many ways in C++, we are particularly interested in two:
/// 1) Stack-allocated objects, which have automatic lifetime management.
/// 2) Dynamically-allocated objects, which should be managed by a stack-allocated object.
///


//============================================================
// Dummy object types for demonstration.
//============================================================

///
/// BaseObject prints to cout when it is created and destroyed.
///
class BaseObject {
public:
	BaseObject( const std::string &name ):
		name( name )
	{
		cout << "Created " << name << endl;
	}

	/// If you are making a class that is intended to be subclassed, declare its destructor virtual.
	/// This allows C++ to do the right thing when destroying a subclass via a pointer to the base class.
	virtual ~BaseObject()
	{
		cout << "Cleaning up BaseObject: " << name << endl;
	}

	/// Do something with the object.
	void printName() const;
	/// For derived classes to be able to redefine functionality,
	virtual void customPrintName() const;

	std::string name;
};

///
/// DerivedObject inherits from BaseObject and prints a bit more on destruction.
///
class DerivedObject : public BaseObject {
public:
	DerivedObject( const std::string &name ):
		BaseObject( name )
	{}

	~DerivedObject()
	{
		cout << "Cleaning up DerivedObject: " << name << endl;
	}

	/// Any method that overrides a base class method should be declared with override at the end.
	/// The override keyword tells the compiler that this should override a base method, and allows
	/// it to notify you if the base method and this one don't match up (by producing an error at compile-time).
	void customPrintName() const override;
};

//=================================================================
// Functions that use the objects, demonstrating parameter passing.
//=================================================================

/// Pass objects by const reference in almost all circumstances.
void useObject( const BaseObject &object )
{
	object.printName();
}

/// If you are going to change an object in your function, pass by reference.
/// Make sure that the function name clearly communicates that it will change the object.
///
/// An alternative (used by Cinder) is to pass by pointer when you will modify the object,
/// since it makes the function clearly different at the call site.
void changeObject( BaseObject &object )
{
	object.name += " has been changed";
}

//============================================================
// Functions demonstrating object creation.
//============================================================

void createStackObjects()
{
	// Stack-allocated objects have automatic lifetime management.
	// They are valid until the block scope they are declared in ends.
	// Blocks are delimited with curly-braces {}.
	BaseObject 		base( "Stack A" );
	DerivedObject derived( "Stack B" );

	cout << endl;
	cout << "Using objects" << endl;

	// We can pass objects by reference or const reference without any formality.
	useObject( base );
	useObject( derived );

	changeObject( base );
	useObject( base );

	cout << endl;
	cout << "Leaving Function" << endl;
}

void createDynamicObjects()
{
	// Dynamically-allocated objects should be stored in a stack-allocated object.
	// C++ provides two such objects that are the most useful: std::shared_ptr and std::unique_ptr
	// We can create these pointer objects with the std::make_shared and std::make_unique functions.
	//
	// When we do managed dynamic allocation, we are really creating two objects:
	// (1) the pointer object on the stack, and
	// (2) the pointed-to object in dynamic memory.
	// The pointer object is used as a handle (or pointer) to the dynamic object, and
	// automatically manages the memory allocation of the dynamic object.

	// Here we create two shared_ptr objects.
	// shared_ptr's are our bread-and-butter for polymorphism and dynamic allocations.
	auto base = make_shared<BaseObject>( "Dynamic A" );
	auto derived = make_shared<DerivedObject>( "Dynamic B" );

	// Unique pointers are more efficient than shared_ptrs, but they cannot be copied.
	// Use them if you need run-time polymorphism, but only manage the object from one place.
	auto unique = make_unique<DerivedObject>( "Dynamic C" );

	cout << endl;
	cout << "Using objects" << endl;
	// To get a reference to the object our pointer object points to, we use the * operator.
	// Then we can pass it to our const T& functions like any stack-allocated object of the same type.
	useObject( *base );
	useObject( *unique );

	cout << endl;
	cout << "Copying shared_ptr<DerivedObject> into shared_ptr<BaseObject>" << endl;
	// Dynamic allocation enables polymorphism.
	// This means our shared_ptr<BaseObject> can refer to any class derived from BaseObject.
	// To demonstrate, we will copy the pointer object to derived into the pointer object to base.
	// Remember this is C++: variables do not change type. The pointer to base can point to any derived type.
	//
	// After we copy a pointer object, the left-hand pointer object refers to the same pointed-to object
	// as the right-hand pointer object.
	// If the previous left-hand pointer object was the last one referring to the pointed-to object, it
	// will destroy the pointed-to object.
	base = derived;

	changeObject( *derived );

	cout << endl;
	cout << "Leaving Function" << endl;
}

///
/// Test program showing destructor behavior.
///
int main( int argc, char const *argv[] )
{
	cout << "Stack Allocated Objects" << endl;
	cout << "=======================" << endl;
	createStackObjects();

	cout << endl;
	cout << "Dynamically Allocated Objects" << endl;
	cout << "=============================" << endl;
	createDynamicObjects();

	return 0;
}

//============================================================
// Object method implementations
//============================================================

void BaseObject::printName() const
{
	// Often, you might have work that must be done whenever a method is called.
	// To facilitate that, create a non-virtual base method that does the setup
	// and calls the virtual method.
	cout << "PrintName: ";

	customPrintName();

	// Here, we guarantee that there is a newline after our custom print statement;
	cout << endl;
}

void BaseObject::customPrintName() const
{
	cout << "BaseObject: " << name;
}

void DerivedObject::customPrintName() const
{
	cout << "DerivedObject: " << name;
}
