#include "utils.cpp"

unordered_map<string, int> LabelTable = {
    {"SP", 0x0000},
    {"LCL", 0x0001},
    {"ARG", 0x0002},
    {"THIS", 0x0003},
    {"THAT", 0x0004},
    {"R0", 0x0000},
    {"R1", 0x0001},
    {"R2", 0x0002},
    {"R3", 0x0003},
    {"R4", 0x0004},
    {"R5", 0x0005},
    {"R6", 0x0006},
    {"R7", 0x0007},
    {"R8", 0x0008},
    {"R9", 0x0009},
    {"R10", 0x000A},
    {"R11", 0x000B},
    {"R12", 0x000C},
    {"R13", 0x000D},
    {"R14", 0x000E},
    {"R15", 0x000F},
    {"SCREEN", 0x4000},  
    {"KBD", 0x6000}     
};

enum InstructionType {
  A_INSTRUCTION = 0, C_INSTRUCTION = 1, L_INSTRUCTION = 2, COMMENT_LINE = 3, NOT_DEFINE = 4
};

class Parser {
  private:
  ifstream File;
  int line_number;
  string current_line;
  bool isFileOpen;
  InstructionType currentInstruction;

  public:
  Parser() : line_number(0), current_line(string("\0")), isFileOpen(false), currentInstruction(NOT_DEFINE) {};
  Parser(const char* input_path);
  virtual ~Parser() {};

  void readNextLine();
  InstructionType findInstruction();

  int getCurrentLineNumber() const;
  string getCurrentLine() const;
  InstructionType getCurrentInstruction() const;
  bool isOpen() const;
};
