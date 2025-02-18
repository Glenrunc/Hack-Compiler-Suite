#ifndef PARSER_HPP
#define PARSER_HPP

#include "utils.hpp"

enum instructionType {
  A_INSTRUCTION = 0,
  C_INSTRUCTION = 1,
  L_INSTRUCTION = 2,
  COMMENT_LINE = 3,
  NOT_DEFINE = 4
};


enum commandType{
  C_ARITHMETIC=0,
  C_PUSH = 1,
  C_POP=2,
  C_LABEL=3,
  C_GOTO=4,
  C_IF=5,
  C_FUNCTION=6,
  C_RETURN=7,
  C_CALL=8,
  C_NOT_DEFINE=9,
  C_COMMENT=10
};
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

  bool isOpen() const { return is_file_open; }
  string getCurrentLine() const { return current_line; }
  int getCurrentLineNumber() const { return line_number; }
};

/**
 * @brief ASM Parser
 * 
 */
class ASMParser : public BaseParser {
private:
  instructionType current_instruction;

public:
  ASMParser(const char *input_path)
      : BaseParser(input_path), current_instruction(NOT_DEFINE){};
  virtual ~ASMParser(){};

  void readNextLine() override;
  void findInstruction() override;

  instructionType getCurrentInstruction() const {return current_instruction;};
};

class VMParser: public BaseParser {
  private:
    commandType current_command;
  public:
    VMParser(const char *input_path): BaseParser(input_path), current_command(C_NOT_DEFINE){};
    void readNextLine() override; 
    void findInstruction() override;
    commandType getCurrentCommand() const {return current_command;};
};
#endif