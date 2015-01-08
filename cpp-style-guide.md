Soso C++ Style
==============

Derived from earlier Soso C++ doc. Discussions or changes to the style may happen in the future.

## Indentation

Use tabs, 2-spaces wide. Note that this markdown document is indented with spaces, since it is (currently) not possible to tell github to change the tab width of code snippets inside markdown files.

### Xcode Setup

Open Xcode preferences and change the indentation settings in the text editing panel.
![xcode indentation settings](https://cloud.githubusercontent.com/assets/81553/5666200/06e320ba-972c-11e4-9f60-8b970f6dc499.png)

As a bonus, you can also tell Xcode to trim trailing whitespace in the editing panel.
![xcode trim trailing whitespace](https://cloud.githubusercontent.com/assets/81553/5666201/06e45c5a-972c-11e4-9a36-4e1f6e8da1e0.png)

### Sublime Text Setup

Open Sublime preferences and add the following options to the json:

```json
"indent_using_spaces": false,
"tab_size": 2,
"trim_trailing_white_space_on_save": true
```

## Variable naming

Member variables don't use prefixes, and are written with initialCapitals (camelCase).

```c++
class Whatever {
  // Member variables are written camelCase.
  // Initialize value of built-in types at declaration.
  float       memberVariable = 1.0f;
  std::string anotherMember;
}
```

Local variables are written with underscore separators.

```c++
float addTwo( float value ) {
  const float value_to_add = 2.0f;
  return value + value_to_add;
}
```

Arguments to methods are prefixed with "i."

```c++
void Class::addToValue( float iValue ) {
  value += iValue;
}
```


## Braces

Braces generally open on the same line, except in constructors with initializer lists. We also write javascript, where braces (practically) must open on the same line, and having consistency across languages is nice.

```c++
namespace example {

void function() {
  // function body...
}

auto fn = [] () {
  // lambda body...
};

class Thing {
public:
  Thing( const Argument &iArgument, const Argument &iAnother );
  float method() const;
private:
  Argument argument;
  Argument another;
}

// Exception, since the initializers make brace placement awkward.
Thing::Thing( const Argument &iArgument, const Argument &iAnother )
: argument( iArgument ),
  another( iAnother )
{}

float Thing::method() const {
  // method body...
}

} // namespace example
```

## Comments

Use only single-line comments `//` to document code. If your comment spans multiple lines, comment out each line individually.

For inline comments, use `//`, for documentation comments (e.g. of class and method declarations), use `///`. The extra slash is a hint to Doxygen and other documentation tools.

Place the comment on the line immediately preceding the thing being commented.

```c++
/// Really long comments should be broken across multiple lines.
/// Each line should be individually commented-out.
/// This helps set the comment apart as a unit in the code.
///
/// You can even have "paragraphs" in your comments if you add empty lines.
/// Don't use the block-comment style /**/, as it can play tricks on you.
namespace comments {

/// Render collection to screen as point sprites.
void renderAsSprites( const std::vector<Type> &points );

}

// In the implementation file, we use // for comments.
// These comments aren't meant for external documentation.
void comments::renderAsSprites( const vector<Type> &points ) {
  // Copy our data over to the GPU
  ...
  // Set up some important OpenGL state
  ...
  // Draw to screen.
  ...
}
```

## Conclusion

The sentiment expressed in the [preamble to BitSquid’s coding style](http://www.bitsquid.se/files/coding_style.html#A common style is good) holds true here. Consistent style helps us read each others code and makes the project cohesive. Some of the choices to that end are arbitrary. Style revision wars do not help us.

Follow the guidelines in this document as you write. If you are working on a section of code that doesn't follow the guide, update it as you are making your changes. Avoid style-only revisions.
