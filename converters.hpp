#ifndef CONVERTERS_HPP
#define CONVERTERS_HPP

#include <string>
#include <cstdint>

// Convert 16-bit signed integer to 16-bit binary string (two's complement)
std::string decToBin(int16_t value);

// Convert 16-bit signed integer to 4-digit hex string (0xFFFF)
std::string decToHex(int16_t value);

// Parse a binary string (e.g. "1010" or "0b1010" or "1111111111111111") to int16_t
// If input longer than 16 bits, low 16 bits are taken.
int16_t binToDec(const std::string &bin);

// Parse a hex string ("0x1A2B" or "1A2B") to int16_t
int16_t hexToDec(const std::string &hex);

// Parse decimal string to int16_t (handles negative)
int16_t decStrToInt16(const std::string &decStr);

#endif // CONVERTERS_HPP
