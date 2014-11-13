
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

///
/// In C++, you can pass function objects around.
/// std::function is a template that describes a call signature.
/// std::functions store a reference to a function that can be called
/// with the signature they define.
///
/// Lambdas can be used to create function objects inline in your code.
/// They can capture variables from the current scope, do any work you want,
/// and call other functions.
///

///
/// Define a few functions with different method signatures.
/// We will use these later
///

int intProducer() {
	cout << "Producing an integer" << endl;
	return 1;
}

void intConsumer( int value ) {
	cout << "Using int: " << value << endl;
}

void functionAndAdaptors() {
	// Define a std::function that takes no parameters and has no return type.
	// We can assign different functions to call from this name later.
	std::function<void ()> function = nullptr;

	// std::functions are comparable as bools.
	// If your function object doesn't refer to a callable function, it will evaluate to false.
	// In those cases, calling the function will fail.
	if( ! function ) {
		cout << "Function doesn't refer to anything yet." << endl;

		try {
			// since function doesn't refer to an implementation yet,
			// calling will throw a std::bad_function_call exception.
			function();
		}
		catch( std::bad_function_call &exc ) {
			cout << "Exception: Bad Function Call. " << exc.what() << endl;
		}
	}

	/// Lambdas can be used as function adapters, allowing us to call functions in contexts
	/// where the parameters may not be available.
	/// Below, we can assign lambdas that adapt our earlier methods to the <void ()> signature of our function.
	function = [] { intProducer(); };
	function();

	function = [] { intConsumer( 5 ); };
	function();
}

void lambdaCapture() {
	/// Lambdas can capture data from the current scope. The variables to capture
	/// are declared in the square brackets [] like function parameters. Providing the
	/// name captures by value, using an & captures by reference.
	int var = 12;
	/// Capture "var" by reference. Changes to var outside will be reflected in the function, and changes to var in the function will be reflected outside.
	/// Be very careful when capturing by reference that your object lifetime is handled correctly.
	auto capture_by_reference = [&var] { var = 5; };
	/// Capture "var" by value. Changes to var after this point don't affect the captured value.
	/// Prefer to capture by value when using lambdas.
	auto capture_by_value = [var] {
		cout << "var's value in lambda: " << var << endl;
	};

	capture_by_reference();
	cout << "var's value: " << var << endl;
	capture_by_value();
}

void lambdaParameters() {
	/// Lambdas can do arbitrary computation. They don't need to call other functions.
	/// You define parameters to a lambda the same way you define parameters for a function.
	auto make_range = [] ( int low, int high ) {
		std::vector<int> range;
		auto begin = std::min( low, high );
		auto end = std::max( low, high );
		while( begin <= end ) {
			range.push_back( begin );
			begin += 1;
		}
		return range;
	};

	auto range = make_range( 11, 37 );
	cout << "Printing range: ";
	for( auto &v : range ) {
		cout << v << ", ";
	}
	cout << endl;
}

int main() {

	functionAndAdaptors();

	lambdaCapture();

	lambdaParameters();
}
