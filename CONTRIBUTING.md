Style Guide & Coding Conventions
================================

## General
- Indentation is to be consistently four spaces, not tabs or a mixture of spaces and tabs.
- All files are to have a single blank line at their end, if possible.
- Prefer C++14 features to C++03 features when possible, and avoid deprecated language features.
- When using C++14 features, try to use those which are supported by at least both clang++ and gcc
- Prefer to use `<c____>` rather than `<____.h>` for C standard library headers
- Headers should be included in this order to reduce pollution: first ChessPlusPlus headers, then library headers, then C++ standard headers.
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
- Prefer inlining functions, ctors, and dtors, so long as they do not increase header file coupling.
- Try to make as many functions `noexcept` as possible, or at least use the conditional `noexcept` syntax.
- If a function is known for throwing exceptions, write `noexcept(false)` as a visual indicator.
- Destructors are `noexcept(true)` by default, do not put the `noexcept` specifier on a dtor unless it is conditional or `noexcept(false)`.
- Try to avoid excess or repetitive "access:" specifiers.
- Avoid strange spaces before open parens and open braces and in other places unless you are lining up code with other code for readability and emphasis of relation.
- There is no line character limit, but that is because you shouldn't have exceedingly long lines (unless they just have exceedingly long identifiers). Instead, avoid deeply nested compound expressions - they reduce readability and hinder understanding of what code is for and/or doing.
- Include guards should mirror the primary namespace + class of the file, e.g. `chesspp::piece::Piece` maps to `chesspp_piece_Piece_HeaderPlusPlus`

## Specifics
One-liners should be **one line**, otherwise they should be in braces:
```cpp
if(condition) one(liner);
//or
if(condition)
{
    really(long(one, liner));
}
```

Constructor initializer lists and class inheritance lists should have each element on their own line and have the same indentation level as the opening brace of the ctor/class:
```cpp
class OurClass
: TheirClassA
, TheirClassB
{
    OurClass()
    : first(element)
    , second(element)
    , nth(element)
    {
        //...
    }
};
```

The `const` keyword is to appear on the right side of types, to be consistent with other uses of the `const` keyword:
```cpp
char const *identifier;
```
It should also _not_ snuggle next to * and &

\* and & should sunggle next to identifiers:
```cpp
void func(ns::ClassName *classname, ns::OtherClass const &otherclass) const
{
    //...
}
```

To suggest changes to this guide, fork the project, make amendments, submit the pull request, and partake in discussion of the changes.
