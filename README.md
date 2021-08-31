# Imap (integer mapping)
Functions to compute the number of bytes, scale factor, and bias to map a floating point value to an integer, given a range and the desired precision.
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)

## Installation
CMake is used to build this library, which is exported as a library target called *imap*. The header is added as:

```
#include "imap/imap.h"
```

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake ..
make
```

This will build the library, an example executable called *imap_example*, and an executable for testing using the Google Test framework, called *imap_test*. The example executable source file is located at *examples/imap_example.cc*.

## Namespace
This library is within the namespace *bfs*.

## Mapping
Floating point data should be mapped to an integer by:

```
I = round(F * S + B)
```

Where *F* is the floating point value, *S* is the scale factor, and *B* is the bias. A rounding operation, should be used to convert the resulting floating point value to an integer. To convert back to floating point, the following algorithm should be used:

```
F = (I - B) / S
```

## Data Structure
All of the functions return the *ImapData* structure. The structure is templated with respect to the floating point type to represent the scale factor and bias.

| Type | Field Name | Description |
| --- | --- | --- |
| std::size_t | num_bytes | The maximum number of bytes needed for storage |
| T | scale_factor | The scale factor, *S*, above |
| T | bias | The bias, *B*, above |

## Functions
Four versions of this algorithm were developed. Two mapping the floating value to a signed integer and two mapping to an unsigned integer. For each, a regular and a greedy version of the algorithm was created. If the range and precision required 1.2 bytes of storage, both versions will need at least 2 bytes of space. The greedy version of the algorithm fully uses the 2 bytes of space to store the same range, improving the precision. The regular version uses the scale factor associated with the original 1.2 byte size requirement leaving the additional storage unused or providing for a greater range of values.

Why would you not always use the greedy version? If you're storing the data in a variable sized integer (i.e. LEB128 or ULEB128) you may want to use the normal version to increase the liklihood that you don't need the full range of bytes leading to storage (or wire) space savings.

**ImapData<T> ImapConfig(T min, T max, T precision)** Computes and returns the *ImapData* structure given the floating point minimum and maximum values along with the desired precision. The mapping is computed to a signed integer.

```C++
/* Map gyro data (+/-2000 deg/s range, 0.1 deg/s precision) */
bfs::ImapData<float> gyro_mapping = bfs::ImapConfig(-2000.0f, 2000.0f, 0.1f);
```

**ImapData<T> ImapGreedyConfig(T min, T max, T precision)** Computes and returns the *ImapData* structure given the floating point minimum and maximum values along with the desired precision. The mapping is computed to a signed integer. This version will fully use the bytes required, improving the precision.
```C++
/* Map gyro data (+/-2000 deg/s range, 0.1 deg/s precision) */
bfs::ImapData<float> gyro_mapping = bfs::ImapGreedyConfig(-2000.0f, 2000.0f, 0.1f);
```

**ImapData<T> UimapConfig(T min, T max, T precision)** Computes and returns the *ImapData* structure given the floating point minimum and maximum values along with the desired precision. The mapping is computed to an unsigned integer.

```C++
/* Map gyro data (+/-2000 deg/s range, 0.1 deg/s precision) */
bfs::ImapData<float> gyro_mapping = bfs::UimapConfig(-2000.0f, 2000.0f, 0.1f);
```

**ImapData<T> UimapGreedyConfig(T min, T max, T precision)** Computes and returns the *ImapData* structure given the floating point minimum and maximum values along with the desired precision. The mapping is computed to an unsigned integer. This version will fully use the bytes required, improving the precision.
```C++
/* Map gyro data (+/-2000 deg/s range, 0.1 deg/s precision) */
bfs::ImapData<float> gyro_mapping = bfs::UimapGreedyConfig(-2000.0f, 2000.0f, 0.1f);
```
