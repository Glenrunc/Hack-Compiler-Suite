#ifndef UTILS_HPP
#define UTILS_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cctype>
#include <sstream>

using namespace std;

extern unordered_map<string, int> LabelTable;
vector<string> tokenize(const string& s);
bool isCorrectlyFormatted(string symbol);

#endif