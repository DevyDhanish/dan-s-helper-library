#pragma once
#include <string>
#include <vector>
// contain alphabets 26 for lower and 26 for upper.
// abcd...z...ABCD...Z
extern const char alphabets[26 + 26 + 1];

// contains number from 0 to 9
extern const char numbers[10 + 1];

// contains all the symbols from the keyboard
extern const char symbols[35 + 1];

extern const char allChars[100];

std::vector<std::string> splitIntoVector(const char *str, char point, uint32_t size);