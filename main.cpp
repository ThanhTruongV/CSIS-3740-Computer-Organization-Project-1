#include <iostream>
#include <string>
#include <limits>
#include "converters.hpp"
#include "alu.hpp"
#include "utils.hpp"

void printAllRepr(int16_t value) {
    std::cout << "Decimal: " << static_cast<int>(value) << "\n";
    std::cout << "Binary : " << decToBin(value) << "\n";
    std::cout << "Hex    : " << decToHex(value) << "\n";
}

int main() {
    std::cout << "=== 16-bit ALU Simulator ===\n";
    std::cout << "Input a number in one of formats:\n";
    std::cout << "  Decimal (e.g. -123)\n";
    std::cout << "  Hex with 0x prefix (e.g. 0x1A2B)\n";
    std::cout << "  Binary with 0b prefix (e.g. 0b1101)\n\n";
    std::cout << "Enter input: ";

    std::string input;
    if (!std::getline(std::cin, input)) return 0;
    // determine format quickly
    try {
        int16_t val;
        bool parsed = false;
        std::string s = input;
        // trim:
        auto ltrim = [](std::string &str){ while (!str.empty() && isspace((unsigned char)str.front())) str.erase(str.begin()); };
        auto rtrim = [](std::string &str){ while (!str.empty() && isspace((unsigned char)str.back())) str.pop_back(); };
        ltrim(s); rtrim(s);
        if (s.rfind("0x", 0) == 0 || s.rfind("0X", 0) == 0) {
            val = hexToDec(s);
            parsed = true;
        } else if (s.rfind("0b", 0) == 0 || s.rfind("0B", 0) == 0) {
            val = binToDec(s);
            parsed = true;
        } else {
            // check if string contains only 0/1 spaces -> treat as binary without prefix
            bool only01 = true;
            for (char c : s) if (!(c=='0' || c=='1' || isspace((unsigned char)c))) { only01 = false; break; }
            if (only01 && !s.empty()) {
                val = binToDec(s);
                parsed = true;
            } else {
                // treat as decimal
                val = decStrToInt16(s);
                parsed = true;
            }
        }

        if (!parsed) {
            std::cout << "Could not parse input.\n";
            return 0;
        }

        std::cout << "\nRepresentations:\n";
        printAllRepr(val);

        // Demo a few ALU operations
        ALU alu;
        Flags f;
        std::cout << "\n--- ALU demo (with flags) ---\n";

        int16_t a = val;
        int16_t b = 1; // example

        int16_t r;

        r = alu.add(a, b, f);
        std::cout << a << " + " << b << " = " << static_cast<int>(r) << "  " << decToBin(r) << "  " << flagsToString(f.Z,f.N,f.C,f.V) << "\n";

        r = alu.sub(a, b, f);
        std::cout << a << " - " << b << " = " << static_cast<int>(r) << "  " << decToBin(r) << "  " << flagsToString(f.Z,f.N,f.C,f.V) << "\n";

        r = alu.BAND(a, b, f);
        std::cout << "AND: " << decToBin(a) << " & " << decToBin(b) << " = " << decToBin(r) << "  " << flagsToString(f.Z,f.N,f.C,f.V) << "\n";

        r = alu.BOR(a, b, f);
        std::cout << " OR: " << decToBin(a) << " | " << decToBin(b) << " = " << decToBin(r) << "  " << flagsToString(f.Z,f.N,f.C,f.V) << "\n";

        r = alu.BXOR(a, b, f);
        std::cout << "XOR: " << decToBin(a) << " ^ " << decToBin(b) << " = " << decToBin(r) << "  " << flagsToString(f.Z,f.N,f.C,f.V) << "\n";

        r = alu.BNOT(a, f);
        std::cout << "NOT: ~" << decToBin(a) << " = " << decToBin(r) << "  " << flagsToString(f.Z,f.N,f.C,f.V) << "\n";

        r = alu.shl(a, 1, f);
        std::cout << "SHL 1: " << decToBin(a) << " << 1 = " << decToBin(r) << "  " << flagsToString(f.Z,f.N,f.C,f.V) << "\n";

        r = alu.shr(a, 1, f);
        std::cout << "SHR 1: " << decToBin(a) << " >> 1 = " << decToBin(r) << "  " << flagsToString(f.Z,f.N,f.C,f.V) << "\n";

    } catch (const std::exception &ex) {
        std::cout << "Error parsing input: " << ex.what() << "\n";
    }

    return 0;
}
