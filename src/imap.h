/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2022 Bolder Flight Systems Inc
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#ifndef SRC_IMAP_H_
#define SRC_IMAP_H_

#if defined(ARDUINO)
#include <Arduino.h>
#endif
#include <cstdint>
#include <cmath>
#include <type_traits>

namespace bfs {

template<typename T>
struct ImapData {
  std::size_t num_bytes;
  T scale_factor;
  T bias;
  T min;
  T max;
  T precision;
};

template<typename T>
constexpr ImapData<T> ImapConfig(const T min, const T max, const T precision) {
  static_assert(std::is_floating_point<T>::value,
                "Only floating point types supported");
  /* Number of bytes needed */
  T vals = std::ceil((max - min) / (static_cast<T>(2) * precision)) +
           static_cast<T>(2);
  T bits = std::ceil(std::log2(vals));
  T bytes = std::ceil(bits / static_cast<T>(8));
  /*
  * Find the scale factor
  * We're using integer range of 2^n - 2 for signed ints
  */
  T sf = (std::pow(static_cast<T>(2), bits) - static_cast<T>(2)) / (max - min);
  /* Find the bias */
  T bias = static_cast<T>(-1) * (std::pow(static_cast<T>(2), bits) -
           static_cast<T>(2)) / static_cast<T>(2) - sf * min;
  ImapData<T> ret;
  ret.num_bytes = static_cast<std::size_t>(bytes);
  ret.scale_factor = sf;
  ret.bias = bias;
  ret.min = min;
  ret.max = max;
  ret.precision = precision;
  return ret;
}

template<typename T>
constexpr ImapData<T> UimapConfig(const T min, const T max, const T precision) {
  static_assert(std::is_floating_point<T>::value,
                "Only floating point types supported");
  /* Number of bytes needed */
  T vals = std::ceil((max - min) / (static_cast<T>(2) * precision)) +
           static_cast<T>(1);
  T bits = std::ceil(std::log2(vals));
  T bytes = std::ceil(bits / static_cast<T>(8));
  /*
  * Find the scale factor
  * We're using integer range of 2^n - 1 for unsigned ints
  */
  T sf = (std::pow(static_cast<T>(2), bits) - static_cast<T>(1)) / (max - min);
  /* Find the bias */
  T bias = static_cast<T>(0) - sf * min;
  ImapData<T> ret;
  ret.num_bytes = static_cast<std::size_t>(bytes);
  ret.scale_factor = sf;
  ret.bias = bias;
  ret.min = min;
  ret.max = max;
  ret.precision = precision;
  return ret;
}

template<typename T>
constexpr ImapData<T> ImapGreedyConfig(const T min, const T max,
                                       const T precision) {
  static_assert(std::is_floating_point<T>::value,
                "Only floating point types supported");
  /* Number of bytes needed */
  T vals = std::ceil((max - min) / (static_cast<T>(2) * precision)) +
           static_cast<T>(2);
  T bits = std::ceil(std::log2(vals));
  T bytes = std::ceil(bits / static_cast<T>(8));
  bits = bytes * static_cast<T>(8);
  /*
  * Find the scale factor
  * We're using integer range of 2^n - 2 for signed ints
  */
  T sf = (std::pow(static_cast<T>(2), bits) - static_cast<T>(2)) / (max - min);
  /* Find the bias */
  T bias = static_cast<T>(-1) * (std::pow(static_cast<T>(2), bits) -
           static_cast<T>(2)) / static_cast<T>(2) - sf * min;
  ImapData<T> ret;
  ret.num_bytes = static_cast<std::size_t>(bytes);
  ret.scale_factor = sf;
  ret.bias = bias;
  ret.min = min;
  ret.max = max;
  ret.precision = precision;
  return ret;
}

template<typename T>
constexpr ImapData<T> UimapGreedyConfig(const T min, const T max,
                                        const T precision) {
  static_assert(std::is_floating_point<T>::value,
                "Only floating point types supported");
  /* Number of bytes needed */
  T vals = std::ceil((max - min) / (static_cast<T>(2) * precision)) +
           static_cast<T>(1);
  T bits = std::ceil(std::log2(vals));
  T bytes = std::ceil(bits / static_cast<T>(8));
  bits = bytes * static_cast<T>(8);
  /*
  * Find the scale factor
  * We're using integer range of 2^n - 1 for unsigned ints
  */
  T sf = (std::pow(static_cast<T>(2), bits) - static_cast<T>(1)) / (max - min);
  /* Find the bias */
  T bias = static_cast<T>(0) - sf * min;
  ImapData<T> ret;
  ret.num_bytes = static_cast<std::size_t>(bytes);
  ret.scale_factor = sf;
  ret.bias = bias;
  ret.min = min;
  ret.max = max;
  ret.precision = precision;
  return ret;
}

}  // namespace bfs

#endif  // SRC_IMAP_H_
