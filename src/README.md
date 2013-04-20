Style Guide & Coding Conventions
================================
- Indentation is to be consistently four spaces, not tabs or a mixture of spaces and tabs.
- All files are to have a single blank line at their end, if possible.
- Prefer C++11 features to C++03 features when possible, and avoid deprecated language features.
- When using C++11 features, try to use those which are supported by at least both clang++ and gcc
- Prefer to use `<c____>` rather than `<____.h>` for C standard library headers
- Prefer use of `class` to `struct` for declaring classes (this means you need to explicitly specify public inheritance).
- Prefer to use file extensions .cpp and .hpp (using .h may cause the file to be detected as C or Objective-C rather than C++)
- Prefer `lowercase` for parameter and local variable names.
- Prefer `UpperCamelCase` for class and type names
- Prefer `lowerCamelCase` for member function names
- Prefer `lower_case_underscore` for private member names
- Prefer `lwrabbrcase` for namespace names
- Braces should be on their own lines, even for empty definitions
- Namespaces cause indentation to occur, inclusion guards do not
- Avoid using raw pointers when possible
- Prefer creating `using` declarations to using raw primitive types
- Avoid use of exceptions when possible
- Avoid ambiguous or non-obvious public interfaces that would otherwise require documentation
- Prefer code that makes less assumptions and allows more flexibility to client code
- Prefer using e.g. functions defined in `<algorithm>` to using common idioms - this allows refactoring to be more obvious and/or straightforward
- First design abstract/high-level/object-oriented code, and optimize later as needed
- Use nameless scopes in functions to emphasize the lifetime of RAII objects
- Place source file helper functions/classes in anonymous namespaces AND declare them static, so as to avoid name/symbol conflicts across irrelevant source files
- Keep clear the separation between client and server behaviors and responsibilities
- Prefer defining one-line accessor functions that don't cause coupling inside the header file.

To suggest changes to this guide, fork the project, make amendments, submit the pull request, and partake in discussion of the changes.
