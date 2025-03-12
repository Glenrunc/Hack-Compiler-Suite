#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include "parser.hpp"

class Translator {
protected:
  const char *output_path;
  ofstream output_file;
  bool is_output_file_open;

public:
  Translator(const char *output_path);
  virtual ~Translator(){};

  virtual void runTranslator() = 0;
};

class Assembler : public Translator {
private:
  ASMParser parser;
  const char *input_path;

public:
  Assembler(const char *input_path, const char *output_path)
      : Translator(output_path), parser(input_path){};
  void runTranslator() override;
};

class VM : public Translator {
private:
  vector<unique_ptr<VMParser>> parser_vector;

public:
  VM(vector<const char *> input_path_vector, const char *output_path);
  void runTranslator() override;
  void writeArithmetic(string arg1);
  void writePushPop(string arg1, int arg2);
};
#endif