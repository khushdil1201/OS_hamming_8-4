#include <iostream>
#include <vector>
#include <bitset>
#include "lib.h"

void displayCommands()
{
    std::cout << "\n1. Encode" << std::endl;
    std::cout << "2. Decode" << std::endl;
    std::cout << "3. Odd parity test" << std::endl;
    std::cout << "Choose a command: ";
}

std::vector<uint8_t> convertToBytes(const std::string &binaryStr)
{
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < binaryStr.size(); i += 4)
    {
        uint8_t value = static_cast<uint8_t>(std::stoi(binaryStr.substr(i, 4), nullptr, 2));
        bytes.push_back(value);
    }
    return bytes;
}

void encodeNumber(unsigned long long number, std::vector<uint8_t> &encodedBytes)
{
    std::string input = std::bitset<64>(number).to_string();
    input.erase(0, input.find_first_not_of('0'));

    std::cout << "Number " << number << " in binary: " << input << std::endl;

    while (input.size() % 4 != 0)
    {
        input = "0" + input;
    }

    std::vector<uint8_t> bytes = convertToBytes(input);
    encodedBytes = hamming8_4::encode(bytes);
}

void decodeBytes(const std::vector<uint8_t> &encodedBytes)
{
    auto decodedBytes = hamming8_4::decode(encodedBytes);

    if (!decodedBytes.empty())
    {
        std::cout << "Decoded data: ";
        for (const auto &byte : decodedBytes)
        {
            std::cout << std::bitset<4>(byte);
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Error during decoding" << std::endl;
    }
}

void testParity(std::vector<uint8_t> &encodedBytes)
{
    int byteIndex, bitIndex;
    std::cout << "Enter byte index and bit index to change: ";
    std::cin >> byteIndex >> bitIndex;

    if (byteIndex > 0 && byteIndex <= encodedBytes.size() && bitIndex >= 1 && bitIndex <= 8)
    {
        encodedBytes[byteIndex - 1] ^= (1 << (bitIndex - 1));
        std::cout << "Modified encoded data: ";
        for (const auto &byte : encodedBytes)
        {
            std::cout << std::bitset<8>(byte) << " ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Invalid byte or bit index!" << std::endl;
    }
}

int main()
{
    unsigned long long number;
    std::vector<uint8_t> encodedBytes;
    bool isEncoded = false;

    std::cout << "Enter a number (decimal): ";
    std::cin >> number;

    while (true)
    {
        displayCommands();

        int command;
        std::cin >> command;

        switch (command)
        {
            case 1:
            {
                encodeNumber(number, encodedBytes);
                isEncoded = true;
                break;
            }
            case 2:
            {
                if (isEncoded)
                {
                    decodeBytes(encodedBytes);
                }
                else
                {
                    std::cout << "Please, encode your data first!" << std::endl;
                }
                break;
            }
            case 3:
            {
                if (isEncoded)
                {
                    testParity(encodedBytes);
                }
                else
                {
                    std::cout << "Please, encode the data first!" << std::endl;
                }
                break;
            }
            default:
                std::cout << "Invalid command!" << std::endl;
        }

        std::cout << "Do you want to continue? (Y/n): ";
        char ch;
        std::cin >> ch;
        if (ch == 'n' || ch == 'N')
        {
            break;
        }
    }

    return 0;
}
