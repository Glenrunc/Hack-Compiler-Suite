#include "translator.hpp"

Translator::Translator(const char *output_path) : output_file(output_path) {
  if (!output_file) {
    cerr << "error when trying to open output file" << endl;
  } else {
    this->is_output_file_open = true;
  }
}

void Assembler::runTranslator() {
  ASMParser temp_parser = ASMParser(this->input_path);

  // First passage
  while (this->parser.isOpen()) {
    parser.readNextLine();
    if (!(this->parser.getCurrentLine().empty())) {
      vector<string> instruction = tokenize(this->parser.getCurrentLine());
      if (this->parser.getCurrentInstruction() == A_INSTRUCTION) {
        addAIntruction(instruction[0]);
      }

      if (this->parser.getCurrentInstruction() == L_INSTRUCTION) {
        addLIntstruction(instruction[0], this->parser.getCurrentLineNumber());
      }
    }
  }

  // Second passage
  while (temp_parser.isOpen()) {
    temp_parser.readNextLine();
    vector<string> instruction = tokenize(temp_parser.getCurrentLine());
    string to_write;
    if (!(temp_parser.getCurrentLine().empty())) {
      if (temp_parser.getCurrentInstruction() == A_INSTRUCTION) {
        this->output_file << parseAInstruction(instruction[0]) << endl;
      }

      if (temp_parser.getCurrentInstruction() == C_INSTRUCTION) {
        this->output_file << parseCInstruction(instruction[0]) << endl;
      }
    }
  }

  this->output_file.close();
}

VM::VM(vector<const char *> input_path, const char *output_path)
    : Translator(output_path) {
  if (!input_path.empty()) {
    for (auto &it : input_path) {
      this->parser_vector.push_back(make_unique<VMParser>(it));
    }
  } else {
    cerr << "No VM files to process !" << endl;
    return;
  }
}

void VM::runTranslator() {
  for (auto &it : this->parser_vector) {
    while (it->isOpen()) {
      it->readNextLine();
      if (it->getCurrentCommand() == C_ARITHMETIC) {
        this->writeArithmetic(it->getArg1());
      } else if (it->getCurrentCommand() == C_POP ||
                 it->getCurrentCommand() == C_PUSH) {
        this->writePushPop(it->getArg1(), it->getArg2());
      }
    }
  }
}

void VM::writeArithmetic(string arg1) {

  this->output_file << "//Write Arithmetic" << endl;
  this->output_file << "@SP" << endl;

  if (arg1 == "add" || arg1 == "sub" || arg1 == "and" || arg1 == "or" ||
      arg1 == "eq" || arg1 == "gt") {
    this->output_file << "AM=M-1" << endl;
    this->output_file << "D=M" << endl;
    this->output_file << "A=A-1" << endl;

    if(arg1 == "add"){this->output_file << "M=M+D" << endl;}
    if(arg1 == "sub"){this->output_file << "M=M-D" << endl;}
    if(arg1 == "and"){this->output_file << "M=M&D" << endl;}
    if(arg1 == "or"){this->output_file << "M=M|D" << endl;}
      

  } else if (arg1 == "not" || arg1 == "neg") {
    this->output_file << "A=M-1" << endl;
    if(arg1 == "not"){this->output_file << "M=!M" << endl;}
    if(arg1 == "add"){this->output_file << "M=-M" << endl;}
      
  }

  
}

void VM::writePushPop(string arg1, int arg2) {
  // TODO
}