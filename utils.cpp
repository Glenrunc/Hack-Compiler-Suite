#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cctype>
#include <sstream>

using namespace std;

std::vector<std::string> tokenize(const std::string& s) {
    std::istringstream iss(s);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}


bool isCorrectlyFormatted(string symbol) {
    bool isValid = true;
    for (char c : symbol) {
        if (!isalnum(c)) {
            isValid = false;
            break;
        }
    }

    return isValid;
}