Source Control
==============

When committing code to your git repository, it's important to remember that each commit should be a single distinguishable change, new feature, or deletion. Source control is not about backing up code in a remote repository, it's about leaving a bread crumb trail which tracks the development of the program's new features, changes and removals in distinguishable chunks.

Some tips on committing:

1) Commit often. Break down changes into unique and distinguishable changes relating to a class, test or file. Your message should begin with the name of the file or class that you modified.

    e.g. "Pawn: Fix Size default value"

2) Amend your commits if you find an error. `$ git commit --amend` lets you modify your latest commit. You can do this to unstage files or stage new changes you've made.

3) Use `$ git commit -p` to split up your changes into different hunks. It's recommended you expand your terminal or console window vertically to see the entire output. Enter `?` at the prompt to see what each option does.

4) Use selective commits e.g. `$ git commit include/bakge/MyChangedFile.h` to commit only hunks from a specific file or set of files.

5) Ensure your working branch is up to date with the corresponding branch in palistov/bakge. This way if you submit a pull request I don't have to dig through a mountain of commits already pushed to my repo. You can do this by doing `$ git pull palistov <branch_name>` (assuming palistov is an alias for my remote repository https://github.com/palistov/bakge)


Style
=====

For consistency across the codebase, a certain coding style is recommended. If you commit code that doesn't meet the styling standards, no worries -- I'll adjust it before finalizing the pull request. Remember that you can always browse existing code for examples of proper style usage.

Except for the following cases, code should match the Linux kernel coding style as described here: https://www.kernel.org/doc/Documentation/CodingStyle


Identifiers
===========

To maintain code readability, use succinct yet descriptive identifiers for variables, types and functions. All identifiers should be camel-cased. Certain abbreviations are allowed when appropriate, and easily understood. (e.g. Num instead of NumberOf)

```
int nplayer; /* BAD */
int NumPlayers; /* GOOD */
```

Iterators or sentinels in for or while loops can be single lowercase characters instead of full words.

```cpp
for(int Value=0;Value<5;++Value) /* Ehh, passable */
    ...
for(int i=0;i<5;++i) /* Just fine */
    ...
```


Enumerations and macros should be in all caps.

```cpp
enum DRAW_TYPE /* GOOD */
{
    ...
};
```

`#define bge_ASSERT ... /* BAD */`


Anything unable to be placed into the bakge namespace (Objective-C code, or macros) should be prefixed with bge and styled appropriately.

`#define BGE_MACRO_SYMBOL ...`

```objc
@implementation bgeObjectiveCClass
...
@end
```


Functions
=========

If a function is a public API call, the identifier should be clear in what it does. Internal functions do not need to have such a level of clarity, but they should still be easily understood by those familiar with the system in which they are used.

```cpp
/* BAD - Reset all what?! */
void ResetAll()
{
    ...
}
```


```cpp
/* GOOD */
void ResetPlayers()
{
    ...
}
```


Types and Classes
=================

Classes and type definitions should aim to provide as much detail about the use of the type as possible.

```cpp
/* BAD */
void SetVelocity(float X, float Y, float Z, float S);
{
    ...
}
```


```cpp
/* GOOD */
void SetVelocity(Vector4 Direction, Meters PerSec)
{
    ...
}
```


Commentation
============

Comment your code! Use the following comment styles as appropriate.

```cpp
// Single-line comment.

/* Single-line comment. */

/* *
 * Multi-line comment.
 * Second line of multi-line comment.
 * */

/*!
 * Doxygen documentation comment (header files only).
 */
```


Whitespace
==========

Indentation is done using 4 spaces. Please don't use tabs! Namespaces and class declarations should begin at column 0. Do not nest namespaces.


General Convention
==================

* Tag your endif preprocessor symbols with the corresponding if's predicate.

    ```cpp
    #ifdef DEFINED_SYMBOL
    ...
    #endif // DEFINED_SYMBOL
    ```

* Always have a newline at the end of a file.

* Avoid declaring typedefs or new data types inside classes.

* Avoid the use of unnamed namespaces.

* Avoid declaring extern or even static global variables in headers. Use static class members with protected or private access instead. This is to protect these variables from being modified by unwarranted means.

* Declaring extern or static variables inside source files (hidden vars) is OK.

* Declaring extern functions inside other functions, then defining them elsewhere is OK.

    ```cpp
    void PublicAPIMethod(int X)
    {
        extern void InternalAPIMethod(int); /* OK */

        InternalAPIMethod(X); /* Defined in SomeOtherSource.cpp */
        ...
    }
    ```

* Put one newline between function definitions and namespace declarations

* Put two newlines between function definitions

* Avoid using a lot of do-while loops. They can be confusing.

* Empty loops are OK but put the semicolon on a new line, indented 4 spaces

    ```cpp
    while(i < 20)
        ;
    ```


* Do not put spaces between control flow statements and their predicates

    ```cpp
    if (i > 12) /* BAD */
        ...
    if(i > 12) /* GOOOD */
        ...
    ```


* Put single lines after control flow statements on a new line

    ```cpp
    if(Win->IsOpen()) return true; /* BAD */

    if(Win->IsOpen()) /* GOOD */
        return true;
    ```


* Else blocks and if blocks should always match each other.

    ```cpp
    if(PlayerOne->IsAlive()) {
        ...
    } else return NULL; /* BAD */

    if(PlayerOne->IsAlive()) {
        ...
    } else {
        return NULL; /* GOOD */
    }
    ```


* Switch statement case labels should line up with their switch statement. The case block code and break (or return, not both) should be indented once. If a default case exists, put it at the end of the switch block. Do not use a break statement in a default case. Put a newline above each case label.

    ```cpp
    switch(PlayerLevel) {

    case 1:
        ...
        return false;

    case 2:
        ...
        break;

    default:
        ...
    }
    ```
