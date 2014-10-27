
// Include our project header.
#include "NamespacesAndAliases.h"

// Include standard library headers.
#include <memory>
#include <functional>
#include <iostream>


/// Declare an alias `DataAggregateRef` for shared_ptr to that type.
/// The `Ref` suffix on a type name is a convention for share_ptr aliases.
using DataAggregateRef = std::shared_ptr<project::DataAggregate>;

/// Declare an alias to the module DataAggregate.
/// There is no ambiguity on the type, since it is in a different namespace from the previous.
using ModuleAggregate = project::module::DataAggregate;

/// Declare that we are using the std namespace implies the std:: prefix
/// on objects, variables, and methods inside the namespace.
/// We do this only in source (not header) files, since implying that we
/// are always using a given namespace can cause compiler ambiguity errors
/// and even unexpected runtime behavior if the compiler chooses incorrectly for you.
///
/// You can think of this as declaring an alias for every std:: object that drops the std::
using namespace std;

using namespace project;

///
/// Test program showing destructor behavior.
///
int main( int argc, char const *argv[] )
{

	auto aggregate = DataAggregate( 1.0f, 2.0f );
	auto agg2 = module::DataAggregate( 10.0f, "hello" );

	return 0;
}

// Define our constructor.
project::DataAggregate::DataAggregate( float iOne, float iTwo ):
	memberOne( iOne ),
	memberTwo( iTwo )
{}

// Define our constructor.
project::module::DataAggregate::DataAggregate( float iValue, const string &iName ):
	value( iValue ),
	name( iName )
{}
