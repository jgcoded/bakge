Bakge has several typedefs that it uses both to clarify the purpose of primitive variables like integers or floating point numbers. Most of these are declared in the Type header located at `include/bakge/core/Type.h` but some other type definitions may be scattered across other headers.


### typedef int Result

Bakge uses integers to represent the results of various operations. To check the result of an operation, compare it to the pre-processor defined constants `BGE_SUCCESS` or `BGE_FAILURE`.


### typedef char Byte

A byte is a single word which is generally used to represent raw data. Using a `Byte` in place of a `char` can have unexpected results, since not all bytes represent an ASCII or printable character.


### typedef ... Uint64

Platform-dependent type definition. Guaranteed to be a 64-bit unsigned integer on any supported platform.


### typedef Uint64 Microsecond

A microsecond is 1 millionth of a second (1.0 E -6 seconds). Using an 8 byte integer to store these values ensures no overflow occurs when the game is run for more than INT_MAX microseconds (which adds up to around 2200 seconds, or slightly less than 40 minutes of running time. Bakge uses microseconds as its the primary unit for time measurement.


### typedef double Seconds

Bakge describes seconds as double-precision floating point numbers. Provided for convenience (typing out a bunch of zeros in your time measurement constants kinda sucks)


### typedef float Scalar

Currently Bakge uses single-precision floating point numbers to represent numbers in math classes. In the future this precision will be able to be changed to double precision using a pre-processor definition.
