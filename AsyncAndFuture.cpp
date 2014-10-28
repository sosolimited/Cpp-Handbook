
#include <future>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

///
/// Test program showing use of std::future and std::async to load data
/// asynchronously, allowing our main loop to continue running while work is done elsewhere.
///

/// Load a file's contents into a string.
///
/// We need a method that will take a bit of time
/// so we can observe the asynchronous behavior.
/// This is the method we will call asynchronously.
std::string loadString( const std::string &path );

int main( int argc, char const *argv[] )
{
	// Our loop control variable.
	bool running = true;

	// Count up our loop iterations so we can show it
	auto loop_count = 0;

	// Construct a lambda function that calls loadString with the argument we want.
	// We can call lambdas just like other functions. Here, we are using one as
	// an adapter: it adapts loadString( string ) into a function that takes no arguments.
	// Requiring no arguments allows us to pass the function to std::async.
	//
	// Detailed information on lambdas is available here:
	// http://msdn.microsoft.com/en-us/library/dd293603.aspx
	auto function = [] () {
		return loadString( "AsyncAndFuture.cpp" );
	};

	// Call the lambda function asynchronously with std::async.
	// The std::launch::async is necessary to make sure it runs in a separate thread.
	future<string> future_text = std::async( std::launch::async, function );

	// Acknowledge the start of loading.
	cout << "Loading" << endl;

	// Loop while the function executes
	while( running )
	{
		// Increment our count.
		loop_count += 1;

		// If our future is connected to a running function.
		if( future_text.valid() )
		{
			// Check the status of our function by waiting for zero nanoseconds.
			// We can wait for an actual amount of time if we have cycles to spare in our main loop.
			// std::chrono literal suffixes are in C++14, and can be referenced here:
			// http://en.cppreference.com/w/cpp/chrono/duration
			auto status = future_text.wait_for( 0ns );
			if( status == std::future_status::ready )
			{
				// Get the actual string from our future string.
				auto text = future_text.get();

				cout << "Loaded string: " << endl;
				cout << text << endl;
			}
		}
		else
		{
			// Our future is no longer valid, which means it either
			// finished running and the result was retrieved, or it was set up incorrectly.
			running = false;
		}
	}

	cout << "Async and Future sample finished" << endl;
	cout << "Looped " << loop_count << " times while loading." << endl;
	return 0;
}

// loadString definition is down here since it's not really important what
// we do to load the string other than knowing file system access can take time.
std::string loadString( const std::string &path )
{
	string text;
	auto file = ifstream( path.c_str() );

	if( file.is_open() )
	{
		string line;

		while( getline( file, line ) )
		{
			text += line + "\n";
		}

		file.close();
	}

	return text;
}
