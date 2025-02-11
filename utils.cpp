#include "utils.hpp"

unordered_map<string, int> labelTable = {
    {"SP", 0x0000},   {"LCL", 0x0001},    {"ARG", 0x0002}, {"THIS", 0x0003},
    {"THAT", 0x0004}, {"R0", 0x0000},     {"R1", 0x0001},  {"R2", 0x0002},
    {"R3", 0x0003},   {"R4", 0x0004},     {"R5", 0x0005},  {"R6", 0x0006},
    {"R7", 0x0007},   {"R8", 0x0008},     {"R9", 0x0009},  {"R10", 0x000A},
    {"R11", 0x000B},  {"R12", 0x000C},    {"R13", 0x000D}, {"R14", 0x000E},
    {"R15", 0x000F},  {"SCREEN", 0x4000}, {"KBD", 0x6000}};

unordered_map<string, string> compTable = {
    {"0", "0101010"},   {"1", "0111111"},   {"-1", "0111010"},
    {"D", "0001100"},   {"A", "0110000"},   {"!D", "0001101"},
    {"!A", "0110001"},  {"-D", "0001111"},  {"-A", "0110011"},
    {"D+1", "0011111"}, {"A+1", "0110111"}, {"D-1", "0001110"},
    {"A-1", "0110010"}, {"D+A", "0000010"}, {"D-A", "0010011"},
    {"A-D", "0000111"}, {"D&A", "0000000"}, {"D|A", "0010101"},

    {"M", "1110000"},   {"!M", "1110001"},  {"-M", "1110011"},
    {"M+1", "1110111"}, {"M-1", "1110010"}, {"D+M", "1000010"},
    {"D-M", "1010011"}, {"M-D", "1000111"}, {"D&M", "1000000"},
    {"D|M", "1010101"}};

unordered_map<string, string> destTable = {
    {"", "000"},  {"M", "001"},  {"D", "010"},  {"MD", "011"},
    {"A", "100"}, {"AM", "101"}, {"AD", "110"}, {"AMD", "111"}};

unordered_map<string, string> jumpTable = {
    {"", "000"},    {"JGT", "001"}, {"JEQ", "010"}, {"JGE", "011"},
    {"JLT", "100"}, {"JNE", "101"}, {"JLE", "110"}, {"JMP", "111"}};

int last_ram_enter = 0;

bool isValidComp(string &comp) {
  set<string> validComp = {"0",   "1",   "-1",  "D",   "A",   "!D",  "!A",
                           "-D",  "-A",  "D+1", "A+1", "D-1", "A-1", "D+A",
                           "D-A", "A-D", "D&A", "D|A", "M",   "!M",  "-M",
                           "M+1", "M-1", "D+M", "D-M", "M-D", "D&M", "D|M"};
  return validComp.find(comp) != validComp.end();
}

bool isValidDest(string &dest) {
  set<string> validDest = {"M", "D", "MD", "A", "AM", "AD", "AMD"};
  return dest.empty() || validDest.find(dest) != validDest.end();
}

bool isValidJump(string &jump) {
  set<string> validJump = {"JGT", "JEQ", "JGE", "JLT", "JNE", "JLE", "JMP"};
  return jump.empty() || validJump.find(jump) != validJump.end();
}

vector<string> tokenize(const string &s) {
  istringstream iss(s);
  vector<string> tokens;
  string token;
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

bool isInLabelTable(string label_name) {
  return labelTable.find(label_name) != labelTable.end();
}

void addAIntruction(string A_instruction) {
  string symbol = A_instruction.substr(1);

  bool isNumber = all_of(symbol.begin(), symbol.end(), ::isdigit);

  if (!isNumber && !isInLabelTable(symbol)) {
    last_ram_enter = (last_ram_enter == 0) ? 16 : last_ram_enter + 1;
    labelTable[symbol] = last_ram_enter;
  }
}

void addLIntstruction(string L_instruction, int line_number) {
  string instruction = L_instruction.substr(1, L_instruction.size() - 2);
  labelTable[instruction] = line_number;
}

string parseCInstruction(string instruction) {
  size_t equalPos = instruction.find('=');
  size_t semicolonPos = instruction.find(';');
  string dest, comp, jump;

  if (equalPos != string::npos) {
    dest = instruction.substr(0, equalPos);
    comp = (semicolonPos != string::npos)
               ? instruction.substr(equalPos + 1, semicolonPos - equalPos - 1)
               : instruction.substr(equalPos + 1);
  } else {
    comp = (semicolonPos != string::npos) ? instruction.substr(0, semicolonPos)
                                          : instruction;
  }

  if (!isValidComp(comp)) {
    cerr << comp << " isn't valid for C-Instruction" << endl;
  }

  if (!isValidDest(dest)) {
    cerr << dest << " isn't valid for C-Instruction" << endl;
  }

  if (semicolonPos != string::npos) {
    jump = instruction.substr(semicolonPos + 1);
  }

  if (!isValidJump(jump)) {
    cerr << jump << " isn't valid for C-Instruction" << endl;
  }

  return "111" + compTable[comp] + destTable[dest] + jumpTable[jump];
}

string parseAInstruction(string instruction) {
  string symbol = instruction.substr(1);
  string A_instruction;

  if (!all_of(symbol.begin(), symbol.end(), ::isdigit)) {
    if (labelTable.find(symbol) == labelTable.end()) {
      cerr << "Erreur : le label '" << symbol << "' n'est pas défini !" << endl;
      return "";
    }
    A_instruction = bitset<15>(labelTable[symbol]).to_string();
  } else {
    int value = stoi(symbol);
    A_instruction = bitset<15>(value).to_string();
  }

  return "0" + A_instruction;
}