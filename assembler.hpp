#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include "parser.hpp"

class Assembler {
private:
  ASMParser parser;
  const char *input_path;
  const char *output_path;
  ofstream output_file;
  bool is_output_file_open;

public:
  Assembler(const char *input_path, const char *output_path);
  virtual ~Assembler(){};

  void runAssembler();
};
#endif