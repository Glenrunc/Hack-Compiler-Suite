#ifndef PARSER_HPP
#define PARSER_HPP

#include "utils.hpp"

/**
 * @brief Interface for different parser (ASM , VM, etc,...)
 *
 */
class BaseParser {
protected:
  ifstream input_file;
  int line_number;
  string current_line;
  bool is_file_open;

public:
  BaseParser() : line_number(0), current_line(""), is_file_open(false) {}
  BaseParser(const char *input_path);
  virtual ~BaseParser(){};

  virtual void readNextLine() = 0;
  virtual void findInstruction() = 0;

  vector<string> parseLine();
  bool isOpen() const { return is_file_open; }
  string getCurrentLine() const { return current_line; }
  int getCurrentLineNumber() const { return line_number; }
};

class ASMParser : public BaseParser {
private:
  instructionType current_instruction;

public:
  ASMParser(const char *input_path)
      : BaseParser(input_path), current_instruction(NOT_DEFINE){};
  virtual ~ASMParser(){};

  void readNextLine() override;
  void findInstruction() override;

  instructionType getCurrentInstruction() const { return current_instruction; };
};

class VMParser : public BaseParser {
private:
  commandType current_command;
  string arg1;
  int arg2;

public:
  VMParser(const char *input_path)
      : BaseParser(input_path), arg1(string("")), arg2(0),
        current_command(C_NOT_DEFINE){};

  void readNextLine() override;
  void findInstruction() override;

  commandType getCurrentCommand() const { return current_command; };
  void findArg1and2(vector<string> line_parsed);

  string getArg1() const { return arg1; };
  int getArg2() const { return arg2; };
};
#endif