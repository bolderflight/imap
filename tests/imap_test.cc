/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2021 Bolder Flight Systems Inc
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


#include "imap.h"
#include "gtest/gtest.h"

/* Test example input */
TEST(Imap, Imap) {
  bfs::ImapData<float> data = bfs::ImapConfig(-2000.0f, 2000.0f, 0.1f);
  float f = 1245.12f;
  int16_t i = std::round(f * data.scale_factor + data.bias);
  float r = (static_cast<float>(i) - data.bias) / data.scale_factor;
  EXPECT_NEAR(f, r, 0.1f);
}
TEST(Imap, ImapGreedy) {
  bfs::ImapData<float> data = bfs::ImapGreedyConfig(-2000.0f, 2000.0f, 0.1f);
  float f = 1245.12f;
  int16_t i = std::round(f * data.scale_factor + data.bias);
  float r = (static_cast<float>(i) - data.bias) / data.scale_factor;
  EXPECT_NEAR(f, r, 0.1f);
}
TEST(Imap, Uimap) {
  bfs::ImapData<float> data = bfs::UimapConfig(-2000.0f, 2000.0f, 0.1f);
  float f = 1245.12f;
  uint16_t i = std::round(f * data.scale_factor + data.bias);
  float r = (static_cast<float>(i) - data.bias) / data.scale_factor;
  EXPECT_NEAR(f, r, 0.1f);
}
TEST(Imap, UimapGreedy) {
  bfs::ImapData<float> data = bfs::UimapGreedyConfig(-2000.0f, 2000.0f, 0.1f);
  float f = 1245.12f;
  uint16_t i = std::round(f * data.scale_factor + data.bias);
  float r = (static_cast<float>(i) - data.bias) / data.scale_factor;
  EXPECT_NEAR(f, r, 0.1f);
}
