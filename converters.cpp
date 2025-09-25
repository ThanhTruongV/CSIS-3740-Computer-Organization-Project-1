#include "converters.hpp"
#include <bitset>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <cctype>

std::string decToBin(int16_t value) {
    // bitset uses unsigned conversion, but two's complement representation is what we want
    std::bitset<16> bits(static_cast<uint16_t>(value));
    return bits.to_string();
}

std::string decToHex(int16_t value) {
    std::stringstream ss;
    ss << "0x" << std::uppercase << std::hex << std::setw(4) << std::setfill('0')
       << (static_cast<uint16_t>(value) & 0xFFFF);
    return ss.str();
}

static std::string trim(const std::string &s) {
    size_t a = 0;
    while (a < s.size() && std::isspace((unsigned char)s[a])) ++a;
    size_t b = s.size();
    while (b > a && std::isspace((unsigned char)s[b-1])) --b;
    return s.substr(a, b-a);
}

int16_t binToDec(const std::string &binRaw) {
    std::string bin = trim(binRaw);
    if (bin.rfind("0b", 0) == 0 || bin.rfind("0B", 0) == 0) bin = bin.substr(2);

    // keep only '0' or '1'
    std::string filtered;
    for (char c : bin) if (c == '0' || c == '1') filtered.push_back(c);

    // if empty, error
    if (filtered.empty()) throw std::invalid_argument("Binary string empty or invalid");

    // if longer than 16, take last 16 bits (low-order)
    if (filtered.size() > 16) filtered = filtered.substr(filtered.size() - 16);

    std::bitset<16> bits;
    // put low-order rightmost char into bitset from right to left
    for (size_t i = 0; i < filtered.size(); ++i) {
        if (filtered[filtered.size() - 1 - i] == '1')
            bits.set(i);
    }
    return static_cast<int16_t>(bits.to_ulong());
}

int16_t hexToDec(const std::string &hexRaw) {
    std::string hex = trim(hexRaw);
    if (hex.rfind("0x", 0) == 0 || hex.rfind("0X", 0) == 0) hex = hex.substr(2);

    // remove non-hex characters (safety)
    std::string filtered;
    for (char c : hex) {
        if (std::isxdigit((unsigned char)c)) filtered.push_back(c);
    }
    if (filtered.empty()) throw std::invalid_argument("Hex string empty or invalid");

    unsigned int value = 0;
    std::stringstream ss;
    ss << std::hex << filtered;
    ss >> value;
    // take low 16 bits
    return static_cast<int16_t>(value & 0xFFFF);
}

int16_t decStrToInt16(const std::string &decStr) {
    std::string s = trim(decStr);
    if (s.empty()) throw std::invalid_argument("Empty decimal string");
    long val = std::stol(s);
    // cast to int16_t -- wraps according to two's complement (but we expect user to supply reasonable values)
    return static_cast<int16_t>(val);
}
