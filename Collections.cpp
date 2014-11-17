
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

/// Vectors are the de-facto sequential container.
/// They store elements in a contiguous block of memory, making iteration and index-based lookup extremely fast.
/// Vectors resize as needed; copying the old contents to the new block of memory when that happens.
/// Due to the way elements in a vector can move around in memory, never take the address of an object in a vector.
std::vector<float>			numberVector;

// Maps are the de-facto associative container.
// They are actually stored as trees, so if you want a hash-based (or true) map,
// you can use std::unordered_map.
std::map<string, float>	numberMap;

// Unordered Maps are true maps, so key-based lookup should be faster than std::map.
std::unordered_map<string, float>	numberUnorderedMap;

void vectorAssignment() {
	// Construct vector with an initializer list, filling it with each value in the list.
	numberVector = { 1, 17.0f, 14.2f, 12.1f, 2, 1.5f, 3.1f, 11.2f };

	// Add elements to the end of a vector with push_back.
	numberVector.push_back( 2.2f );
}

void vectorRetrieval() {
	// Prefer the use of range-based for loops.
	// The typed element to the left of the colon will be filled with each
	// value in the collection on the right side of the colon in order.
	for( auto &number : numberVector ) {
		cout << number << ", ";
	}
	cout << endl;

	// Using square braces doesn't check whether you are past the end.
	// This can be dangerous, since we can manipulate memory that doesn't belong to us.
	// Here, we read past the end of the vector. We will probably get a nonsense value.
	//
	// This is bad news, since the compiler can't help us, and the debugger can't either.
	// We will get undefined, unexpected behavior which is almost always not good.
	// If we wrote anything to this position in the vector, we would be asking for
	// a mysterious crash later.
	cout << "Accessing past end with [] (DON'T DO THIS) => ";
	cout << numberVector[5] << endl;

	// Prefer the use of .at( index ) to bracket indexing.
	// .at( index ) is range-checked, so it will crash if you try to
	// access past the end of your vector. This is a GOOD THING, because
	// it lets us know that we made a mistake in our access code.
	cout << numberVector.at( 0 ) << endl;

	// We run the following access in a try-catch since we know it will
	// crash as it is an out-of-range access and .at() is checked.
	//
	// Generally, we don't use try-catch around .at() calls, since we want
	// the program to crash during testing so we can fix the issue.
	//
	// If you were debugging in Xcode or Visual Studio without the try/catch,
	// the program would halt at this point and open the debugger so you could
	// figure out what you were doing wrong.
	try {
		cout << "Accessing past end with .at() => ";
		cout << numberVector.at( 5 ) << endl;
	}
	catch( std::out_of_range &exc ) {
		cout << "Exception: out of range: " << exc.what() << endl;
	}

	// You can conveniently get the first and last values in a collection:
	cout << numberVector.front() << ", " << numberVector.back() << endl;

	// If you need to iterate through two collections simultaneously,
	// consider whether you can combine them into a single collection.
	// The std::pair and std::tuple types can help with this.
}

void vectorRemoval() {
	// You should only remove elements from the end of a vector, since removing them
	// from anywhere else would force the rest of the vector's contents to be copied
	// over one position. Fortunately, the STL provides ways to move everything we may want
	// to remove to the end of the vector.

	// pop_back() removes the last element in the vector.
	numberVector.pop_back();

	// Erase removes a range of elements specified by iterators.
	// To get a nice set of iterators to remove from the vector, we first
	// rearrange things so all the items to remove are at the end of the vector.
	auto remove_begin = std::remove_if( numberVector.begin(), numberVector.end(), []( float element ) {
		return element > 10.0f;
	} );

	// Now we can remove all the elements from the beginning of the removed set to
	// the end of the vector.
	numberVector.erase( remove_begin, numberVector.end() );

	for( auto &number : numberVector ) {
		cout << number << ", ";
	}
	cout << endl;

}

void mapAssignment() {
	numberMap["one"] = 1;
	numberMap["two"] = 2;
	numberMap["soso"] = 100;

	numberUnorderedMap["one"] = 2;
	numberUnorderedMap["two"] = 4;
	numberUnorderedMap["soso"] = 200;

	// Like vectors, we can also assign maps with an initializer list.
	// We need to initialize each key-value pair for each entry in the map.
	numberUnorderedMap = { { "one", 3 }, { "two", 6 }, { "soso", 300 } };

	// Maps also provide the insert() method.
	numberUnorderedMap.insert( { "five", 500 } );
}

void mapRetrieval() {
	// Prefer the use of range-based for loops.
	// In a map, each item is a key-value pair, so iteration returns both.
	// Note that the order of iteration is unrelated to the order of insertion.

	cout << "map" << endl;
	for( auto &pair : numberMap ) {
		cout << pair.first << " => " << pair.second << endl;
	}

	cout << "unordered_map" << endl;
	for( auto &pair : numberUnorderedMap ) {
		cout << pair.first << " => " << pair.second << endl;
	}

	// We can also use key-based retrieval for our maps.
	cout << "['soso']: " << numberUnorderedMap["soso"] << endl;
	cout << "['two']:  " << numberMap["two"] << endl;

	// Using square brackets will insert a default value if no value exists,
	// so be careful if you are looking up contents this way.
	// This is not nearly as disastrous as accessing past the end of a vector,
	// but it's still something to be careful of.
	cout << "['undefined']: " << numberUnorderedMap["undefined"] << endl;

	// Consider using .at(key) or .find( key ) to retrieve values from maps.
	// .at throws an exception if no key was set, while find returns the end iterator.
	auto iter = numberMap.find( "undefined" );
	if( iter != numberMap.end() ) {
		cout << "['undefined'] was in map: " << iter->second << endl;
	}
	else {
		cout << "['undefined'] was not in map" << endl;
	}
}

void mapRemoval() {
	// Removing items from a map is done by key using the erase() method.
	numberMap.erase( "one" );
	// It is safe to erase things that aren't in the map.
	numberMap.erase( "seventeen" );

	numberUnorderedMap.erase( "soso" );
	numberUnorderedMap.erase( "two" );

	cout << "map" << endl;
	for( auto &pair : numberMap ) {
		cout << pair.first << " => " << pair.second << endl;
	}

	cout << "unordered_map" << endl;
	for( auto &pair : numberUnorderedMap ) {
		cout << pair.first << " => " << pair.second << endl;
	}
}

void sortingAndConversion() {
	// Create a map of words to "counts"
	// We will copy this map into a vector so we can use some STL algorithms
	// on the data, particularly sorting.
	map<std::string, int> wordCountMap = { {"rabbit", 4},
		{"hare", 3},
		{"bunny", 7},
		{"coney", 12},
		{"duck", 3}
	};

	// Create a vector that contains (string, int) pairs to hold data from the map.
	// Make an alias for std::pair<std::string, int>, because that is wild to read.
	using WordCount = std::pair<std::string, int>;
	vector<WordCount>	wordCounts;

	// Assign the word map data to our word counts.
	// This replaces any existing data in the vector.
	wordCounts.assign( wordCountMap.begin(), wordCountMap.end() );
	// Add the contents of wordCounts() to the end of our vector.
	// We are adding to the end so we can have duplicates to remove later.
	wordCounts.insert( wordCounts.end(), wordCountMap.begin(), wordCountMap.end() );

	// Print our results
	cout << "Map contents copied to vector (twice)" << endl;
	for( auto &p : wordCounts ) {
		cout << p.first << ": " << p.second << ", ";
	}
	cout << endl;

	// When sorting with the STL, you provide the range that you want to sort.
	// If it can, the STL will figure out some kind of default sorting.
	std::sort( wordCounts.begin(), wordCounts.end() );

	cout << "Default-sorted vector contents" << endl;
	for( auto &p : wordCounts ) {
		cout << p.first << ": " << p.second << ", ";
	}
	cout << endl;

	// Now that the vector is sorted, we can remove duplicates if we want to.
	// Like most removal operations, this is in two steps.
	// First we arrange the elements so that the duplicates are at the end of the array.
	// The std::unique() algorithm moves all duplicates to the end and returns the "end"
	// of the range of unique elements.
	auto duplicate_begin = std::unique( wordCounts.begin(), wordCounts.end() );
	// Now we erase all the duplicate elements from the end of the vector.
	wordCounts.erase( duplicate_begin, wordCounts.end() );

	cout << "Unique vector contents" << endl;
	for( auto &p : wordCounts ) {
		cout << p.first << ": " << p.second << ", ";
	}
	cout << endl;

	// You can provide a comparator function for std::sort to tell it how to sort elements.
	// We opt to provide our comparator as a lambda.
	// The comparator should return true if the lhs element should precede the rhs element.
	// See http://www.cplusplus.com/reference/algorithm/sort/ for more.
	//
	// We use the stable_sort() function here, an alternative to sort().
	// When elements are equivalent, stable_sort() doesn't change the order in which they appear.
	// Surprisingly, it is also comparable to or faster than sort in speed.
	std::stable_sort( wordCounts.begin(), wordCounts.end(), [] (const WordCount &lhs, const WordCount &rhs) {
		// We want the biggest numbers first,
		// so we return whether the lhs element is greater than the rhs element.
		return lhs.second > rhs.second;
	} );

	cout << "Numerically sorted (non-ascending)" << endl;
	for( auto &p : wordCounts ) {
		cout << p.first << ": " << p.second << ", ";
	}
	cout << endl;
}

int main() {
	cout << endl;
	cout << "Sequential Containers" << endl;
	cout << "=====================" << endl;
	vectorAssignment();
	vectorRetrieval();
	cout << endl;
	cout << "Removing elements" << endl;
	vectorRemoval();

	cout << endl;
	cout << "Associative Containers" << endl;
	cout << "======================" << endl;
	mapAssignment();
	mapRetrieval();
	cout << endl;
	cout << "Removing elements" << endl;
	mapRemoval();

	cout << endl;
	cout << "Sorting Elements and Copying between Container Types" << endl;
	cout << "====================================================" << endl;
	sortingAndConversion();
}
