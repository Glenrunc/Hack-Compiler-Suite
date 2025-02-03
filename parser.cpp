#include "parser.hpp"

Parser::Parser(const char* input_path) : File(input_path), line_number(0), current_line(string("\0")), currentInstruction(NOT_DEFINE) {
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

int Parser::getCurrentLineNumber() const {
  return this->line_number;
}

string Parser::getCurrentLine() const {
  return this->current_line;
}

bool Parser::isOpen() const {
  return this->isFileOpen;
}

InstructionType Parser::getCurrentInstruction() const {
  return this->currentInstruction;
}

InstructionType Parser::findInstruction() {

  InstructionType instruction = NOT_DEFINE;

  string currentLine = this->getCurrentLine();

  if (currentLine.empty()) {
    return NOT_DEFINE;
  }

  if (current_line.size() >= 2 && current_line[0] == '/' && current_line[1] == '/') {
    instruction = COMMENT_LINE;
  }

  if (current_line[0] == '@') {
    vector<string> tokens = tokenize(current_line);

    if (tokens.size() == 1) {
      if (isCorrectlyFormatted(current_line.substr(1))) {
        instruction = A_INSTRUCTION;
      } else {
        cerr << "line: " << this->getCurrentLine() << " - " << "  A-Instruction must be composed of only with digit and/or letter";
      }
    } else {
      cerr << "line: " << this->getCurrentLine() << " - " << "  A-Instruction must be composed of a single word";
    }
  }

  if(current_line[0] == '('){
    vector<string> tokens = tokenize(current_line);

    if(tokens[0].back() == ')'){
      if(isCorrectlyFormatted(tokens[0].substr(1,tokens[0].size()-2))){
        instruction = L_INSTRUCTION;
        if(tokens.size() >= 2 && tokens[1].size()>= 2 && !(tokens[1][0] == '/' && tokens[1][1] == '/')){
          cerr << "line: " << this->getCurrentLine() << " - " << " To many words on the same line";
        }
      }else{
        cerr << "line: " << this->getCurrentLine() << " - " << "  L-Instruction must be composed of only with digit and/or letter";
      }
    }else{
      cerr << "line: " << this->getCurrentLine() << " - " << " ')' is missing";
    }
  }

}