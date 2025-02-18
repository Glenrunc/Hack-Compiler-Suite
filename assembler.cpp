#include "assembler.hpp"

Assembler::Assembler(const char *input_path, const char *output_path)
    : parser(input_path), input_path(input_path), output_path(output_path),
      output_file(output_path) {
  if (!output_file) {
    cerr << "error when trying to open output file" << endl;
  } else {
    this->is_output_file_open = true;
  }
}

void Assembler::runAssembler() {
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