// Copyright (c) 2017 The CRC32C Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef CRC32C_CRC32C_H_
#define CRC32C_CRC32C_H_

// The API exported by the CRC32C project.

#include <cstddef>
#include <cstdint>
#include <string>

namespace crc32c {

// Extends "crc" with the CRC32 of "count" bytes in the buffer pointed by
// "data".
uint32_t Extend(uint32_t crc, const uint8_t* data, size_t count);

// Computes the CRC32C of "count" bytes in the buffer pointed by "data".
inline uint32_t Crc32c(const uint8_t* data, size_t count) {
  return Extend(0, data, count);
}

// Computes the CRC32C of "count" bytes in the buffer pointed by "data".
inline uint32_t Crc32c(const char* data, size_t count) {
  return Extend(0, reinterpret_cast<const uint8_t*>(data), count);
}

// Computes the CRC32C of the string's content.
inline uint32_t Crc32c(const std::string& string) {
  return Crc32c(reinterpret_cast<const uint8_t*>(string.data()),
                string.size());
}

#if defined(__has_include)
#if __has_include(<string_view>)
// Visual Studio provides a <string_view> header even in C++11 mode. When
// included, the header issues an #error. (C1189)
#if !defined(_MSC_VER) || __cplusplus >= 201703L
#include <string_view>

// Comptues the CRC32C of the bytes in the string_view.
inline uint32_t Crc32c(const std::string_view& string_view) {
  return Crc32c(reinterpret_cast<const uint8_t*>(string_view.data()),
                string_view.size());
}

#endif  // !defined(_MSC_VER) || __cplusplus >= 201703L
#endif  // __has_include(<string_view>)
#endif  // defined(__has_include)

}  // namespace crc32c


#endif  // CRC32C_CRC32C_H_
