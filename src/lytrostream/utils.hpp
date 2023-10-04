// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence
// (https://opensource.org/license/gpl-3-0/)

#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <string>

inline std::string
string_to_hex (const std::string &input)
{
  static const char hex_digits[] = "0123456789ABCDEF";

  std::string output;
  output.reserve (input.length () * 2);
  for (unsigned char c : input)
    {
      output.push_back (hex_digits[c >> 4]);
      output.push_back (hex_digits[c & 15]);
    }

  return output;
}

inline int
bitsToInt (char *bits, size_t blockSize, int offset = 0)
{
  int res = 0;
  for (size_t idx = 0; idx < blockSize; idx++)
    {
      res = res
            | int ((unsigned char)bits[offset + idx]
                   << (sizeof (bits) * (blockSize - 1 - idx)));
    }
  return res;
}

inline int
missingBits (size_t length, size_t blockLength)
{
  return (length % blockLength != 0) ? blockLength - length % blockLength : 0;
}

#endif // UTILS_H