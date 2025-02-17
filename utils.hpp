#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <bitset>
#include <cctype>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

extern int last_ram_entry;
extern unordered_map<string, int> LabelTable;
extern unordered_map<string, string> compTable;
extern unordered_map<string, string> destTable;
extern unordered_map<string, string> jumpTable;

bool isValidComp(string &comp);
bool isValidDest(string &dest);
bool isValidJump(string &jump);

vector<string> tokenize(const string &s);
bool isCorrectlyFormatted(string symbol);

void addAIntruction(string A_instruction);
void addLIntstruction(string L_instruction, int line_number);
string parseCInstruction(string instruction);
string parseAInstruction(string instruction);

bool isInLabelTable(string label_name);
#endif