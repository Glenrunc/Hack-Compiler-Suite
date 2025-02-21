#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include "parser.hpp"

class Translator {
protected:
  const char *output_path;
  const char* input_path;
  ofstream output_file;
  bool is_output_file_open;

public:
  Translator(const char *output_path, const char* input_path);
  virtual ~Translator(){};

  virtual void runTranslator() = 0;
};


class Assembler : public Translator{
  private:
    ASMParser parser;
  public:
    Assembler(const char* input_path, const char* output_path): Translator(output_path,input_path), parser(input_path){};
    void runTranslator() override;
};

class VM : public Translator{
  private: 
    VMParser parser;
  public:
    VM(const char* input_path, const char* output_path): Translator(output_path, input_path), parser(input_path){};
    void runTranslator() override;
};
#endif