#include "parser.hpp"

Parser::Parser(const char* input_path)
    : input_file(input_path),
      line_number(0),
      current_line(string("\0")),
      current_instruction(NOT_DEFINE) {
  if (!input_file) {
    cerr << "Error when trying to open this file" << endl;
  } else {
    this->is_file_open = true;
  }
}

void Parser::readNextLine() {
  if (getline(this->input_file, this->current_line)) {
    if (!(this->current_line.empty())) {
      this->findInstruction();
      if (this->current_instruction != COMMENT_LINE) {
        this->line_number++;
      }
    }
  } else {
    if (this->input_file.eof()) {
      this->current_line = "";
    } else if (this->input_file.fail()) {
      cerr << "Error when trying to read line" << endl;
    }
    this->is_file_open = false;
    this->input_file.close();
  }
}

int Parser::getCurrentLineNumber() const { return this->line_number; }

string Parser::getCurrentLine() const { return this->current_line; }

bool Parser::isOpen() const { return this->is_file_open; }

InstructionType Parser::getCurrentInstruction() const {
  return this->current_instruction;
}

void Parser::findInstruction() {
  InstructionType instruction = NOT_DEFINE;

  string currentLine = this->getCurrentLine();

  if (currentLine.empty()) {
    instruction = NOT_DEFINE;
  } else if (current_line.size() >= 2 && current_line[0] == '/' &&
             current_line[1] == '/') {
    instruction = COMMENT_LINE;
  } else if (current_line[0] == '@') {
    vector<string> tokens = tokenize(current_line);

    if (tokens.size() == 1) {
      if (isCorrectlyFormatted(current_line.substr(1))) {
        instruction = A_INSTRUCTION;
      } else {
        cerr << "line: " << this->getCurrentLine() << " - "
             << "  A-Instruction must be composed of only digit and/or letter";
      }
    } else {
      cerr << "line: " << this->getCurrentLine() << " - "
           << "  A-Instruction must be composed of a single word";
    }
  } else if (current_line[0] == '(') {
    vector<string> tokens = tokenize(current_line);

    if (tokens[0].back() == ')') {
      if (isCorrectlyFormatted(tokens[0].substr(1, tokens[0].size() - 2))) {
        instruction = L_INSTRUCTION;
        if (tokens.size() >= 2 && tokens[1].size() >= 2 &&
            !(tokens[1][0] == '/' && tokens[1][1] == '/')) {
          cerr << "line: " << this->getCurrentLine() << " - "
               << " To many words on the same line";
        }
      } else {
        cerr << "line: " << this->getCurrentLine() << " - "
             << "  L-Instruction must be composed of only digit and/or letter";
      }
    } else {
      cerr << "line: " << this->getCurrentLine() << " - " << " ')' is missing";
    }
  } else {
    instruction = C_INSTRUCTION;
  }

  this->current_instruction = instruction;
}

