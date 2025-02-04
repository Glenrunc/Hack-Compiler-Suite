#ifndef PARSER_HPP
#define PARSER_HPP

#include "utils.hpp"

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
  void findInstruction();

  int getCurrentLineNumber() const;
  string getCurrentLine() const;
  InstructionType getCurrentInstruction() const;
  bool isOpen() const;
};

#endif