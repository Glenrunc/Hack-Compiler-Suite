#ifndef PARSER_HPP
#define PARSER_HPP

#include "utils.hpp"

enum InstructionType {
  A_INSTRUCTION = 0,
  C_INSTRUCTION = 1,
  L_INSTRUCTION = 2,
  COMMENT_LINE = 3,
  NOT_DEFINE = 4
};

class Parser {
private:
  ifstream input_file;
  int line_number;
  string current_line;
  bool is_file_open;
  InstructionType current_instruction;

public:
  Parser(): line_number(0), current_line(string("")), is_file_open(false),current_instruction(NOT_DEFINE){};
  Parser(const char *input_path);
  virtual ~Parser(){};

  void readNextLine();
  void findInstruction();

  int getCurrentLineNumber() const;
  string getCurrentLine() const;
  InstructionType getCurrentInstruction() const;
  bool isOpen() const;
};
#endif