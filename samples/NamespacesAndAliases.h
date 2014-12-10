
// Use pragma once to make sure this header file is included only once.
#pragma once

#include <string>

///
/// Namespaces allow us to group large sections of code together and write
/// clear names for the types within each section.
///
/// Aliases allow us to derive clear names from verbose types where needed.
/// Often, you can just use auto to handle the capture of a verbose type.
/// When you need to store a verbose type as a class member or declare it
/// as a function parameter type, aliases are extremely helpful in keeping things legible.
///

///
/// In general, we declare a namespace for the project we are working on.
/// This prevents naming conflicts between different sections of our code.
///
namespace project {

/// Create a data aggregate type in our project namespace.
struct DataAggregate {
	DataAggregate() = default;
	DataAggregate( float iOne, float iTwo );

	float memberOne = 0.0f;
	float memberTwo = 0.0f;
};

/// Since the closing brace of the namespace is often far from the opening one,
/// we comment the closing brace with the declaration we used to open the namespace.
} // namespace project

/// You can reopen namespaces anywhere to add things to them.
/// This is handy since you will often have several files contributing methods
/// and class definitions to the same namespace.
namespace project {

/// You can declare namespaces within other namespaces.
/// Typically, we don't want to go more than two deep to avoid over-specifying things.
///
/// You might have a namespace for each element of your project, like:
/// project::wind::, project::water::, project::soil::,
/// with each having their own data and view types.
///
///
/// This namespace is project::module.
namespace module {
	/// Create a data aggregate type in our module namespace.
	struct DataAggregate
	{
		DataAggregate() = default;
		DataAggregate( float iValue, const std::string &iName );

		float value = 0;
		std::string name;
	};
} // namespace module

} // namespace project

/// Looking forward to making this example less abstract,
/// I am thinking about how to demonstrate breaking things into modules.
namespace project {

namespace water {
	struct Data {

	};
} // namespace water

namespace wind {
	/// For starters, just use the same data type as water.
	/// If in the future we need a custom wind data type, we
	/// could replace this alias with the custom type without needing
	/// to change our code that uses the data.
	///
	/// This style of aliasing is called "lifting," as the type Data
	/// is lifted from the project::water:: namespace into the current one.
	using Data = water::Data;
} // namespace wind

namespace soil {
	/// Soil isn't simulated the same way as wind and water, so we have different data for it.
	struct Data {

	};
} // namespace soil


} // namespace project
