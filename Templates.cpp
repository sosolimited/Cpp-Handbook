
#include <vector>
#include <iostream>

using namespace std;

///
/// Templates allow us to write code that can operate on any type.
/// They enable compile-time polymorphism: the template is defined based
/// on what types use it.
///
/// While you may not write many templates yourself, you will use them
/// whenever you create a dynamically allocated object or store a collection
/// of objects in an STL container.
///

/// Define a function template for accumulate.
/// accumulate sums all the values in a collection.
/// Note that the values can be of any type as long as it provides a `+=` operator.
/// The typename, `T` is used wherever the concrete type is in the final version.
template<typename T>
T accumulate( T start, const std::vector<T> &collection ) {
	for( const auto &t : collection ) {
		start += t;
	}
	return start;
}

int main() {

	// The STL, or standard template library, uses templates extensively to provide
	// containers and algorithms that work with any type.
	std::vector<int> integers = { 1, 2, 3, 4, 5, 12 };
	std::vector<float> floats = { 1.5f, 2.0f, 33.3f };
	std::vector<double> doubles = { 1.2, 3.3, 4.4, 6.6, 9.12 };

	// Templates can perform type deduction based on the arguments provided.
	// Since the types of the start and collection parameters match below,
	// the compiler can figure out the rest.
	cout << "Integers: " << accumulate( 0, integers ) << endl;
	cout << "Floats:   " << accumulate( 0.0f, floats ) << endl;
	cout << "Doubles:  " << accumulate( 0.0, doubles ) << endl;

	// Often, the compiler may not be able to deduce all the template types from the
	// arguments to your method. In those cases, you can help it along by filling in
	// the template parameters yourself.
	// Template parameters are passed in angle-brackets, <>
	int total = accumulate<int>( 1.0f, integers );
	cout << "Total:    " << total << endl;
}
