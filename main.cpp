#include "lib.h"

int main()
{
    unsigned long long number;
    std::vector<uint8_t> encodedBytes;
    bool isEncoded = false;

    std::cout << "Enter a number (decimal): ";
    std::cin >> number;

    while (true)
    {
        hamming8_4::displayCommands();

        int command;
        std::cin >> command;

        switch (command)
        {
            case 1:
            {
                hamming8_4::encodeNumber(number, encodedBytes);
                isEncoded = true;
                break;
            }
            case 2:
            {
                if (isEncoded)
                {
                    hamming8_4::decodeBytes(encodedBytes);
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
                    hamming8_4::testParity(encodedBytes);
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
