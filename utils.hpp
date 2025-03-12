#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <bitset>
#include <cctype>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
enum instructionType {
  A_INSTRUCTION = 0,
  C_INSTRUCTION = 1,
  L_INSTRUCTION = 2,
  COMMENT_LINE = 3,
  NOT_DEFINE = 4
};

enum commandType {
  C_ARITHMETIC = 0,
  C_PUSH = 1,
  C_POP = 2,
  C_LABEL = 3,
  C_GOTO = 4,
  C_IF = 5,
  C_FUNCTION = 6,
  C_RETURN = 7,
  C_CALL = 8,
  C_NOT_DEFINE = 9,
  C_COMMENT = 10
};

extern int last_ram_entry;
extern unordered_map<string, int> LabelTable;
extern unordered_map<string, string> compTable;
extern unordered_map<string, string> destTable;
extern unordered_map<string, string> jumpTable;
extern unordered_map<string, commandType> commandTable;

bool isValidComp(string &comp);
bool isValidDest(string &dest);
bool isValidJump(string &jump);
bool isValidSegment(string &segment);

vector<string> tokenize(const string &s);
bool isCorrectlyFormatted(string symbol);

void addAIntruction(string A_instruction);
void addLIntstruction(string L_instruction, int line_number);
string parseCInstruction(string instruction);
string parseAInstruction(string instruction);

bool isInLabelTable(string label_name);
#endif