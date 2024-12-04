#ifndef HAMMING_CODE_H_INCLUDED
#define HAMMING_CODE_H_INCLUDED

#include <iostream>
#include <cstdint>
#include <bitset>
#include <vector>

namespace hamming8_4
{

    uint8_t encodeBit(uint8_t dataByte);

    std::vector<uint8_t> encode(const std::vector<uint8_t> &dataBytes);

    uint8_t decodeBit(uint8_t encodedByte, int byteIndex);

    std::vector<uint8_t> decode(const std::vector<uint8_t> &encodedBytes);

}

#endif // HAMMING_CODE_H_INCLUDED
