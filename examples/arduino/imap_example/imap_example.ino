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

void setup() {
  /* Mapping output, single precision */
  bfs::ImapData<float> gyro_mapping;
  /*
  * Get configuration to map to a signed integer, gyro example (+/-2000 deg/s,
  * 0.1 deg/s precision)
  */
  gyro_mapping = bfs::ImapConfig(-2000.0f, 2000.0f, 0.1f);
  Serial.println("Gyro Map to Signed Integer:");
  Serial.print("Bytes: ");
  Serial.println(gyro_mapping.num_bytes);
  Serial.print("Scale factor: ");
  Serial.println(gyro_mapping.scale_factor);
  Serial.print("Bias: ");
  Serial.println(gyro_mapping.bias);
  /*
  * Get configuration to map to a signed integer using a greedy algorith, which
  * will compute the required bytes and fully use the bytes required improving
  * the precision. Gyro example (+/-2000 deg/s, 0.1 deg/s precision)
  */
  gyro_mapping = bfs::ImapGreedyConfig(-2000.0f, 2000.0f, 0.1f);
  Serial.println("Gyro Map to Signed Integer, Greedy:");
  Serial.print("Bytes: ");
  Serial.println(gyro_mapping.num_bytes);
  Serial.print("Scale factor: ");
  Serial.println(gyro_mapping.scale_factor);
  Serial.print("Bias: ");
  Serial.println(gyro_mapping.bias);
  /*
  * Get configuration to map to a unsigned integer, gyro example (+/-2000 deg/s,
  * 0.1 deg/s precision)
  */
  gyro_mapping = bfs::UimapConfig(-2000.0f, 2000.0f, 0.1f);
  Serial.println("Gyro Map to Unsigned Integer:");
  Serial.print("Bytes: ");
  Serial.println(gyro_mapping.num_bytes);
  Serial.print("Scale factor: ");
  Serial.println(gyro_mapping.scale_factor);
  Serial.print("Bias: ");
  Serial.println(gyro_mapping.bias);
  /*
  * Get configuration to map to a unsigned integer using a greedy algorith,
  * which will compute the required bytes and fully use the bytes required
  * improving the precision. Gyro example (+/-2000 deg/s, 0.1 deg/s precision)
  */
  gyro_mapping = bfs::UimapGreedyConfig(-2000.0f, 2000.0f, 0.1f);
  Serial.println("Gyro Map to Unsigned Integer, Greedy:");
  Serial.print("Bytes: ");
  Serial.println(gyro_mapping.num_bytes);
  Serial.print("Scale factor: ");
  Serial.println(gyro_mapping.scale_factor);
  Serial.print("Bias: ");
  Serial.println(gyro_mapping.bias);
}

void loop() {}
