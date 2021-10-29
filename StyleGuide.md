# TPG++ Style Guide

The following style guide is based on the Google C++ Style Guide. Things that work for us have been lifted
directly, things that don't have been ignored. Some things have been altered to better suit our pipeline. 
This document will be further beautified at a later date and is semi-living, meaning changes may occur over
time. Any updates will be announced. 

## Goals
* *Style rules should pull their weight*: rules will be added here because they offer a significant contribution based on the following principles.
* *Optimize for the reader, not the writer*: readability is more important than being a code wizard in a bubble.
* *Be consistent*: if you decide to use a certain code structure, use it the same way every time.
* *Avoid surprising and dangerous constructions*: "use judiciously" will be an ongoing motto. Fucking overloaded operators.
* *Concede to optimization when necessary*: sometimes it's faster to do something fast than beautifully. Both is best.
* *Ensure the style guide is flexible!*: this will be updated as it needs to be updated. That said, some things exist in this guide for a reason. Understand the reason before attempting to change it.

## C++ Versioning
Target C++17. C++20 is a major release, akin to C++11 and until we know what the content changes are, we won't be directly supporting it (although it's likely our code will still compile).

## C++ and Header Files
Every C++ source file will end with .cpp and will have an associated C++ header ending with .h. This is true with few exceptions, which include unit test files and a main function source file.

## Self-Contained Headers
Header files should be self-contained (compile on their own) and end in .h. 	

Template and inline functions should be declared in the same file as their declarations. 
	
## The #define Guard
All header files should have #define guards to prevent multiple inclusion. The format of the symbol name should be \<PROJECT\>\_\<PATH\>\_\<FILE\>\_H\_.

To guarantee uniqueness, they should be based on the full path in a project's source tree. For example, the file foo/src/bar/baz.h in project foo should have the following guard:
```c++
#ifndef FOO_BAR_BAZ_H_
#define FOO_BAR_BAZ_H_

...
#endif  // FOO_BAR_BAZ_H_
```

## Forward Declarations
Function definitions should be included in a .h file. Don't use forward declarations in your .cpp files. 
	
## Inline Functions
Define inline functions only when they are small. Preferrably 10 lines or fewer. Don't inline loops or recursion, for the love of god.

## Names and Order of Includes
Includes should be presented in the following order:
		
1. The header for the code currently being tested/implemented.
2. A blank line
3. C system headers (more precisely: headers in angle brackets with the .h extension), e.g. <unistd.h>, <stdlib.h>.
4. A blank line
5. C++ standard library headers (without file extension), e.g. <algorithm>, <cstddef>.
6. A blank line
7. Other libraries' .h files.
8. Your project's other .h files.
		
For example, if your project is in src/foo/internal/fooserver.cpp:
	
```c++
#include "foo/server/fooserver.h"

#include <sys/types.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/commandlineflags.h"
#include "foo/server/bar.h"
```

## Local Variables
Local variables should always be declared with an initialization.
		
## Static and Global Variables
Don't declare any static variables. They have a lifetime equal to program life, regardless of their scope, and can introduce difficult to find bugs when other parts of a program reference static variables contained in an instantiated object scope.

# Classes
	
## Doing Work in Constructors
Constructors should never call virtual functions. If error handling is an issue, consider using a build factory or an Init/Create style object initialization.
	
## Implicit Conversions
Don't ever use one class implicitly where another class is explicitly expected, except in the event of upcasting. Don't ever downcast.
		
## Structs vs. Classes
Use a struct only for passive objects that carry data; everything else is a class.

## Structs vs. Pairs and Tuples
Prefer to use a struct in all cases, especially when the values contained can have meaningful names.

## Inheritance
Interface inheritance should be used almost exclusively, either through fully abstract classes and methods or via the use of templates. Implementation inheritance should be avoided as much as possible.
		
## Operator Overloading
Overload operators with good judgment and common sense. When overloading operators, try to stay	as close to the given operator's original functionality as possible. In the case where the intent of the overload is not immediately obvious, ensure a comment is added to any relevant statement with a reference to the overloaded operator in question.
	
## Access Control
Make classes' data members private, unless they are constants.
	
## Declaration Order
A class definition should start with public, followed by protected, followed by private. Empty sections should be excluded.
	
# Functions
	
## Output Parameters
Don't use pass by reference or pointers to create output parameters. All outputs should be provided via return statements. 
	
## Write Short Functions
Keep functions short (40 lines or less). If functions are getting longer, consider refactoring to break the function into several smaller functions.
	
## Reference Arguments
Reference arguments should be declared constant in the function parameters to prevent references changing, but allowing the values to be modified.
	
## Function Overloading
Most of our overloading will be class constructors. You may overload a function when there are no semantic differences between variants.
	
## Default Arguments
Follow similar rules to the function overloading section.
		
## Trailing Return Type Syntax
Unless there is an incredibly pressing need, stick to the old return type declarations on functions.

## Casting
All same-type arithmetic casting should be done with eh C++11 brace style. All other casting should be performed using the static_cast<type>(), const_cast, and reinterpret_cast functions. Please do not use C-style casting in the form of type(value) and (type)value.
	
## Streams
Streams should only be used in specific situations, favoring printf and fprintf for output instead. I/O streams can be useful for logging and debugging purposes, but should never be user-facing.
	
## Preincrement and Predecrement 
In scenarios where the order of increment/decrement isn't relevant (iterators, for example), use the preincrement/predecrement form to avoid unnecessary copy overhead.

## Integer Types
Of the built-in C++ integer types, the only one used is int. If a program needs a variable of a different size, use a precise-width integer type from <stdint.h>, such as int16_t. If your variable represents a value that could ever be greater than or equal to 2^31 (2GiB), use a 64-bit type such as int64_t. Keep in mind that even if your value won't ever be too large for an int, it may be used in intermediate calculations which may require a larger type. When in doubt, choose a larger type.
		
In most cases within our design documentation, we will explicitly state the size of the integer	to be used in that particular implementation.
	
_*Tentative*_: Fast types may be used as long as the minimum bit length matches the expectation	in the design document.

Unsigned integers should only be used when truly applicable, such as representing a binary value. Representing non-negative numbers should be done by assertion.

## Preprocessor Macros
*TODO: We'll come back to this section after the design document is made.*
	
## 0 and nullptr/NULL
Use '\0' for null characters, NULL for all other null values, and nullptr for null pointers, which ensures type safety.
	
## sizeof
Whenever possible, use sizeof(variableName) not sizeof(typeName).
	
## Type Deduction
Avoid as much as possible. Use type deducation (T cast and auto types) when it would benefit the reader or there is a large variety of incoming data types.
	
## Lambda Expressions
Use common sense when implementing lambda functions. Don't place them everywhere throughout your code. Instead, use them in convenient ad-hoc situations where defining a full function would be wasteful or reduce readability, such as defining comparison conditions for sort functions.
	
## Template Metaprogramming
In general, avoid template metaprogramming. If this becomes an issue for your software, we can generate exceptions on a needed basis.
	
## Nonstandard Extensions
We are going to stick as closely to the C++17 standard as possible. Don't use compiler extensions, and definitely completely avoid nonstandard extensions.
		
## Aliases
Public aliases are for the benefit of an API's user, and should be clearly documented. It should be noted that, as standard, the stdint.h library's main integer types will be aliased to remove trailing type signifiers (_t).
	
# Naming
	
## General Rules
Names should be clear within the context. If explanation is required, include a descriptive comment. In our code we will use the following structure for naming conventions:
			
* Variables -> Camel Case
* Functions -> Camel Case
* Classes   -> Pascal Case
		
In each case, a word is defined as either a single word or acronym. Thus, startCPU() should actually be written as startCpu(). This applies to all structures.
	
## File Names and File Structure
File should contain at most one class and the name should be descriptive of that class. If no class is defined within a file, then a title should be given based on contents. 
		
File names should be all lowercase and may include underscore ("\_") characters to separate words and descriptors. For example, your useful class file should be named "my_useful_class.cpp".
	
## Type Names
Aside from the integer types mentioned in the aliases section, all type names should follow the Pascal Case formatting style.
	
## Variable Naming
Constant variable names should begin with a lowercase k and follow the Camel Case style.
	
## Function Naming
Function names should follow the Camel Case style.
	
# Comments
	
## Comment Style
Use // for all regular comments, including block comments. /* */ should not be used.
	
## Doxygen Style
Our projects will use Doxygen to produce JavaDocs-style documentation for our code files. Doxygen supports JavaDocs-style commenting to identify when a documentation comment is present, thus Doxygen comments should begin with /\*\* and end with \*/. This is an exception to the standard comment style. The manual for using Doxygen comments can be found at: http://www.doxygen.nl/manual/index.html
	
## File Comments
Every file should start with a file comment block, including the license boilerplate. After the boilerplate is added, the file comment should contain information about the contents of a file.
	
## Class Comments
Every class should have a Doxygen comment header applied to it, describing the functionality and what types of data the class manages. The comment should also include an example of the standard method for initializing and using a class (within reason).
	
## Function Declaration Comments
Every function declaration should have a Doxygen comment header applied, discussing the following information:
			
1. What the inputs and outputs are.
2. For class member functions: whether the object remembers reference arguments beyond the duration of the method call, and whether it will free them or not.
3. If the function allocates memory that the caller must free.
4. Whether any of the arguments can be a null pointer.
5. If there are any performance implications of how a function is used.
		
## Variable Comments
Local variable names should generally be descriptive enough to give the user an idea of what they're used for, within the context. 
		
Global and class variables should be commented with programmer intention and their default value. 
Give a brief description of what the variable will be used for.
		
## Implementation Comments
Explanatory comments should be presented before a piece of code with a non-obvious execution.
		
_Line-end comments should never be used._
	
## TODO Comments
Use TODO comments for code that is temporary, a short-term solution, or good enough, but not perfect.
	
TODOs should include the string TODO in all caps, followed by the name of the person who created it, followed by an explanation of why the code snippet exists. It is not necessarily the creator's responsibility to resolve the TODO and their comment should include a definite date, time, or condition under which the code should be updated/completed.

# Formatting

## Line Length
In general, a single line of text in your files can be at most 80 characters long.
		
A line may exceed 80 characters if it is:

1. A comment line which is not feasible to split without harming readability, ease of cut and paste or auto-linking -- e.g. if a line contains an example command or a literal URL longer than 80 characters.
2. A raw-string literal with content that exceeds 80 characters. Except for test code, such literals should appear near the top of a file.
3. An include statement.
4. A header guard.
		
## Spaces vs. Tabs
Use only spaces, and indent 4 spaces at a time. We will exclusively use spaces for indentation. 

Do not use any tabs in your code. Set your editor to emit spaces on tabs.
	
## Function Declarations
Return type on the same line as function name, parameters on the same line if they fit. Wrap parameter lists which do not fit on a single line as you would wrap arguments in a function call.
		
Functions look like this:
```c++
ReturnType ClassName::FunctionName(Type par_name1, Type par_name2) 
{
	DoSomething();
	...
}
```
If you have too much text to fit on one line:
```c++
ReturnType ClassName::ReallyLongFunctionName(Type par_name1, Type par_name2,
	Type par_name3) 
{
	DoSomething();
	...
}
```
or if you cannot fit even the first parameter:
```c++
ReturnType LongClassName::ReallyReallyReallyLongFunctionName(
		// 8 space indent
		Type par_name1,  
		Type par_name2,
		Type par_name3) 
{
	// 4 space indent
	DoSomething();  
	...
}
```
Some points to note:

1. Choose good parameter names.
2. The open parenthesis is always on the same line as the function name.
3. There is never a space between the function name and the open parenthesis.
4. There is never a space between the parentheses and the parameters.
5. The open curly brace is always on the the start of the next line after the function header.
6. The close curly brace is either on the last line by itself.
7. All parameters should be aligned if possible.
8. Default indentation is 4 spaces.
9. Wrapped parameters have an 8 space indent.
	
## Lambda Expressions
Format parameters and bodies as for any other function, and capture lists like other comma-separated lists. Short lambdas may be written inline as function arguments.
	
## Floating Point Literals
Floating-point literals should always have a radix point, with digits on both sides, even if they use exponential notation. Example:
```c++	
float f = 1.0f;
float f2 = 1;
long double ld = -0.5L;
double d = 1248.0e6;
```
## Function Calls
Either write the call all on a single line, wrap the arguments at the parenthesis, or start the arguments on a new line indented by four spaces and continue at that four space indent. In the absence of other considerations, use the minimum number of lines, including placing multiple arguments on each line where appropriate.
	
## Braced Initializer List Format
Format a braced initializer list exactly like you would format a function call in its place.
	
## Conditionals
Prefer no spaces inside parentheses. The if and else keywords belong on separate lines. All conditionals should have the open brace on its own line and every keyword/parameter should have braces, even if it will contain a single line of code, to promote creating easier to maintain code. Example:
```c++		
if (condition) 
{  
	...
} 
else if (...)
{
	...
} 
else 
{
	...
}
```
## Loops
Loops should maintain the same format as described throughout functions and conditionals.

## Loop Iteration
Prioritize iterators wherevever possible. If iterators are not possible or infeasible, use a loop and leave a comment explaining the design decision so that the reader can avoid any pitfalls that may arise from an iterator implementation.

## Pointer and Reference Expressions
No spaces around period or arrow. Pointer operators do not have trailing spaces.

The following are examples of correctly-formatted pointer and reference expressions:
```c++
x = *p;
p = &x;
x = r.y;
x = r->y;
```
Note that:

1. There are no spaces around the period or arrow when accessing a member.
2. Pointer operators have no space after the * or &.

When declaring a pointer variable or argument, you must place the asterisk adjacent to the type:
```c++
char* c;
const std::string& str;
```
Multiple variables should never be declared on a single line to prevent confusion with pointers, references, and value declarations.
	
## Return Values
Do not needlessly surround the return expression with parentheses.

Use parentheses in return expr; only where you would use them in x = expr;.
	
## Variable and Array Initialization
Since our projects all use warning level 4 (one step before Wall), we will exclusively use = for variable value assignment:
```c++	
int x = 3;
std:string name = "Some Name";
```
## Class Format:
Sections in public, protected, and private order, each indented two spaces.
	
## Constructor Initialization Lists
These may be all on one line or with subsequent lines indented four spaces.
	
## Horizontal Whitespace
Use of horizontal whitespace varies by context. Never put trailing whitespace on the end of a line.
