
#include <iostream>

#include <vector>
#include <array>
#include <map>
#include <unordered_map>

// Use the std:: namespace to reduce typing.
// Only ever make using namespace statements in implementation files.
// If you use them in headers, you are entering a world of ambiguous symbol errors and worse.
using namespace std;

///
/// Demonstrates different container types and their use.
///
///

// Vectors are the de-facto sequential container.
std::vector<float>			numberVector;
// Maps are the de-facto associative container.
// (They are actually stored as trees)
std::map<string, float>	numberMap;
// Unordered Maps are true maps, so key-based lookup should be faster than std::map.
std::unordered_map<string, float>	numberUnorderedMap;

void vectorAssignment()
{
	// Construct vector with an initializer list, filling it with each value in the list.
	numberVector = { 1, 2, 1.5f, 3 };
}

void vectorRetrieval()
{
	cout << "Vector Retrieval" << endl;
	// Prefer the use of range-based for loops.
	// The typed element to the left of the colon will be filled with each
	// value in the collection on the right side of the colon in order.
	for( auto &number : numberVector )
	{
		cout << number << endl;
	}

	// Using square braces doesn't check whether you are past the end.
	// This can be dangerous, since we can manipulate memory that doesn't belong to us.
	// Here, we read past the end of the vector. We will probably get a nonsense value.
	cout << "Access past end with [] => ";
	cout << numberVector[5] << endl;

	// Prefer the use of .at( index ) to bracket indexing.
	// .at( index ) is range-checked, so it will crash if you try to
	// access past the end of your vector. This is a GOOD THING, because
	// it lets us know that we made a mistake in our access code.
	cout << numberVector.at( 0 ) << endl;

	// We run the following access in a try-catch since we know it will
	// crash as it is an out-of-range access and .at() is checked.
	try
	{
		cout << "Access past end with .at() => ";
		cout << numberVector.at( 5 ) << endl;
	}
	catch( std::exception &exc )
	{
		cout << "Error: " << typeid(exc).name() << ": " << exc.what() << endl;
	}

	// You can conveniently get the first and last values in a collection:
	cout << numberVector.front() << ", " << numberVector.back() << endl;

	// If you need to iterate through two collections simultaneously,
	// consider whether you can combine them into a single collection.
	// The std::pair and std::tuple types can help with this.
}

void mapAssignment()
{
	numberMap["one"] = 1;
	numberMap["two"] = 2;
	numberMap["soso"] = 100;

	numberUnorderedMap["one"] = 2;
	numberUnorderedMap["two"] = 4;
	numberUnorderedMap["soso"] = 200;

	// We can also assign with an initializer list.
	// This constructs a map that replaces the previous one in numberUnorderedMap
	numberUnorderedMap = { { "one", 3 }, { "two", 6 }, { "soso", 300 } };
	numberUnorderedMap.insert( { "five", 500 } );
}

void mapRetrieval()
{
	// Prefer the use of range-based for loops.
	// In a map, each item is a key-value pair, so iteration returns both.
	// Note that the order of iteration is unrelated to the order of insertion.

	cout << "map Retrieval" << endl;
	for( auto &pair : numberMap )
	{
		cout << pair.first << " => " << pair.second << endl;
	}

	cout << "unordered_map Retrieval" << endl;
	for( auto &pair : numberUnorderedMap )
	{
		cout << pair.first << " => " << pair.second << endl;
	}
}

int main( int argc, char const *argv[] )
{
	vectorAssignment();
	vectorRetrieval();
	mapAssignment();
	mapRetrieval();

	return 0;
}
