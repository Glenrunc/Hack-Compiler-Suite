#include "parser.hpp"

Parser::Parser(const char* input_path) : File(input_path), line_number(0) {
  if (!File) {
    cerr << "Error when trying to open this file" << endl;
  } else {
    this->isFileOpen = true;
  }
}

void Parser::readNextLine() {
  if (getline(this->File, this->current_line)) {
    this->line_number++;
  } else {
    if (this->File.eof()) {
      this->current_line = "";
    } else if (this->File.fail()) {
      cerr << "Error when trying to read line" << endl;
    }
    this->File.close();
    this->isFileOpen = false;
  }
}

int Parser::getLineNumber() const { return this->line_number; }
string Parser::getCurrentLine() const { return this->current_line; }

bool Parser::isOpen() const { return this->isFileOpen; }

CommandType Parser::getCurrentCommand() const { return this->currentCommand; }