// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence (https://opensource.org/license/gpl-3-0/)

#pragma once

#ifndef UTILS_H
#define UTILS_H

int bitsToInt(char* bits, size_t blockSize, int offset = 0)
{
    int res = 0;
    for(size_t idx = 0; idx < blockSize; idx++)
    {
        res = res | int((unsigned char)bits[offset+idx] << (sizeof(bits) * (blockSize - 1 - idx)));
    }
    return res;
}

int missingBits(size_t length, size_t blockLength)
{
    return (length % blockLength != 0) ? blockLength - length % blockLength : 0;
}

#endif //UTILS_H