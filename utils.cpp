#include "utils.hpp"
#include <sstream>

std::string flagsToString(bool Z, bool N, bool C, bool V) {
    std::ostringstream ss;
    ss << "Z=" << (Z?1:0) << " N=" << (N?1:0) << " C=" << (C?1:0) << " V=" << (V?1:0);
    return ss.str();
}
