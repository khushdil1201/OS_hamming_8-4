## Hamming (8,4) Encoding and Decoding Project
# Overview
This project implements the Hamming (8,4) code, a method for error detection and correction. It encodes 4 bits of data into 8 bits by adding parity bits. The program supports encoding, decoding, and parity testing, enabling detection and correction of single-bit errors.

# Project Structure
The project consists of the following files:

lib.h
Header file containing declarations of encoding and decoding functions.
lib.cpp
Implementation of Hamming (8,4) encoding and decoding logic. Includes error correction.
main.cpp
Provides an interactive interface for encoding, decoding, and testing parity functionality.
CMakeLists.txt
Configuration file to build the project using CMake.


# Functionalities

Encoding
Converts a user-provided number into a binary sequence, then encodes it using Hamming (8,4).
Output: Original 4-bit chunks and corresponding 8-bit encoded values.

Decoding
Takes encoded data, detects errors, corrects single-bit errors, and decodes it back to the original 4-bit data.
Detects uncorrectable double-bit errors and notifies the user.

Parity Testing
Allows the user to introduce errors in the encoded data by flipping specific bits.
Verifies the ability of the Hamming code to detect and correct these errors.
