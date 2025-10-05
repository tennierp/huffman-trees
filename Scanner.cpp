#include "Scanner.hpp"
#include <utility>
#include <iostream>
#include <fstream>
#include <vector>

#include "utils.hpp"

Scanner::Scanner(std::filesystem::path inputPath) {
    inputPath_ = inputPath;
}

// Tokenize into memory (according to the Rules in this section).
error_type Scanner::tokenize(std::vector<std::string>& words) {
    std::ifstream infile(inputPath_);

    if (!infile.is_open()) return UNABLE_TO_OPEN_FILE;

    words.clear();

    std::string token = readWord(infile);

    while (!token.empty()) {
        words.push_back(token);
        token = readWord(infile);
    }

    return NO_ERROR;
}

// Read the next token from 'in'. Returns empty string when no more tokens.
std::string Scanner::readWord(std::istream &in) {
    std::string token;
    char currentChar;

    while (in.get(currentChar)) {
        if (isalpha(currentChar)) {
            token.push_back(tolower(currentChar));
        } else if (currentChar == '\'' && isalpha(in.peek()) && !token.empty()) {
            token.push_back('\'');
            in.get(currentChar);
            token.push_back(tolower(currentChar));
        } else {
            if (!token.empty()) {
                break;
            }
        }
    }

    return token;
}