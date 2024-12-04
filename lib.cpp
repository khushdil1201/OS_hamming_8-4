#include "lib.h"
#include <iostream>
#include <bitset>

namespace hamming8_4
{

    uint8_t encodeBit(uint8_t byte)
    {
        bool d1 = (byte >> 3) & 1;
        bool d2 = (byte >> 2) & 1;
        bool d3 = (byte >> 1) & 1;
        bool d4 = (byte >> 0) & 1;

        bool p1 = 1 ^ d1 ^ d3 ^ d4;
        bool p2 = 1 ^ d1 ^ d2 ^ d4;
        bool p3 = 1 ^ d1 ^ d2 ^ d3;
        bool p4 = 1 ^ p1 ^ p2 ^ p3 ^ d1 ^ d2 ^ d3 ^ d4;

        return (p1 << 7) | (d1 << 6) | (p2 << 5) | (d2 << 4) |
               (p3 << 3) | (d3 << 2) | (p4 << 1) | d4;
    }

    std::vector<uint8_t> encode(const std::vector<uint8_t> &bytes)
    {
        std::vector<uint8_t> encodedBytes;
        for (uint8_t byte : bytes)
        {
            uint8_t encodedByte = encodeBit(byte);
            std::cout << std::bitset<4>(byte) << " -> " << std::bitset<8>(encodedByte) << std::endl;
            encodedBytes.push_back(encodedByte);
        }
        return encodedBytes;
    }

    uint8_t decodeBit(uint8_t encodedByte, int byteIndex)
    {
        bool p1 = (encodedByte & 0b10000000) != 0;
        bool p2 = (encodedByte & 0b00100000) != 0;
        bool p3 = (encodedByte & 0b00001000) != 0;
        bool p4 = (encodedByte & 0b00000010) != 0;
        bool d1 = (encodedByte & 0b01000000) != 0;
        bool d2 = (encodedByte & 0b00010000) != 0;
        bool d3 = (encodedByte & 0b00000100) != 0;
        bool d4 = (encodedByte & 0b00000001) != 0;

        // Check parity bits
        bool A = (p1 ^ d1 ^ d3 ^ d4) == 1;
        bool B = (p2 ^ d1 ^ d2 ^ d4) == 1;
        bool C = (p3 ^ d1 ^ d2 ^ d3) == 1;
        bool D = (p1 ^ p2 ^ p3 ^ p4 ^ d1 ^ d2 ^ d3 ^ d4) == 1;

        // If a parity check fails but overall parity is correct, return error marker
        if ((!A || !B || !C) && D)
            return 0b10000000;

        // Calculate the erroneous bit position
        int errorPosition = (!A) + (!B * 2) + (!C * 4) + (!D * 8);
        if (errorPosition > 0) {
            std::cout << "In byte " << byteIndex << ", a bit error was corrected at ";

            switch (errorPosition) {
                case 8:
                    std::cout << "bit 2." << std::endl;
                    break;
                case 12:
                    std::cout << "bit 4." << std::endl;
                    break;
                case 10:
                    std::cout << "bit 6." << std::endl;
                    break;
                case 9:
                    std::cout << "bit 8." << std::endl;
                    break;
                case 15:
                    d1 ^= 1;
                    std::cout << "bit 7." << std::endl;
                    break;
                case 14:
                    d2 ^= 1;
                    std::cout << "bit 5." << std::endl;
                    break;
                case 13:
                    d3 ^= 1;
                    std::cout << "bit 3." << std::endl;
                    break;
                case 11:
                    d4 ^= 1;
                    std::cout << "bit 1." << std::endl;
                    break;
            }
        }

        // Reconstruct the decoded data byte
        return (d1 << 3) | (d2 << 2) | (d3 << 1) | d4;
    }

    std::vector<uint8_t> decode(const std::vector<uint8_t> &encodedBytes)
    {
        std::vector<uint8_t> decodedBytes;
        int byteIndex = 1;

        for (uint8_t encodedByte : encodedBytes)
        {
            uint8_t decodedByte = decodeBit(encodedByte, byteIndex);
            if (decodedByte == 0b10000000)
            {
                std::cout << byteIndex << ". " << std::bitset<8>(encodedByte) << " -> Double error detected" << std::endl;
                return {};
            }
            std::cout << byteIndex << ". " << std::bitset<8>(encodedByte) << " -> " << std::bitset<4>(decodedByte) << std::endl;
            decodedBytes.push_back(decodedByte);
            byteIndex++;
        }

        return decodedBytes;
    }

}
