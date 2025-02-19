#include "parser.hpp"

BaseParser::BaseParser(const char *input_path)
    : input_file(input_path), line_number(0), current_line(string("")) {
  if (!input_file) {
    cerr << "Error when trying to open this file" << endl;
  } else {
    this->is_file_open = true;
  }
}

vector<string> BaseParser::parseLine() {
  vector<string> tokens = tokenize(this->current_line);
  vector<string> result;

  for (size_t i = 0; i < tokens.size(); ++i) {
    size_t pos = tokens[i].find("//");

    if (i == 0 && pos == 0) {
      return {};
    }

    if (pos != string::npos) {
      if (pos > 0) {
        result.push_back(tokens[i].substr(0, pos));
      }
      break;
    }

    result.push_back(tokens[i]);
  }

  return result;
}

void ASMParser::readNextLine() {
  while (getline(this->input_file, this->current_line) &&
         this->current_line.empty()) {
  }

  if (!this->current_line.empty()) {
    this->findInstruction();
    if (this->current_instruction != COMMENT_LINE &&
        this->current_instruction != L_INSTRUCTION) {
      line_number++;
    }
  }

  if (this->input_file.eof()) {
    this->is_file_open = false;
    this->input_file.close();
  }
}

void ASMParser::findInstruction() {
  instructionType instruction = NOT_DEFINE;

  string current_line = this->getCurrentLine();

  if (!current_line.empty()) {
    while (!current_line.empty() && current_line[0] == ' ') {
      current_line = current_line.substr(1);
    }

    if (current_line.size() >= 2 && current_line[0] == '/' &&
        current_line[1] == '/') {
      instruction = COMMENT_LINE;
    } else if (current_line[0] == '@') {
      vector<string> tokens = tokenize(current_line);

      if (tokens.size() == 1) {
        if (isCorrectlyFormatted(current_line.substr(1))) {
          instruction = A_INSTRUCTION;
        } else {
          cerr
              << "line: " << this->getCurrentLine() << " - "
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
          cerr
              << "line: " << this->getCurrentLine() << " - "
              << "  L-Instruction must be composed of only digit and/or letter";
        }
      } else {
        cerr << "line: " << this->getCurrentLine() << " ->" << " ')' is missing"
             << endl;
      }
    } else {
      instruction = C_INSTRUCTION;
    }
  }

  this->current_instruction = instruction;
}

void VMParser::readNextLine() {
  while (getline(this->input_file, this->current_line) &&
         this->current_line.empty()) {
  }

  if (!this->current_line.empty()) {
    this->findInstruction();
    if (this->current_command != C_COMMENT &&
        this->current_command != C_LABEL) {
      this->line_number++;
    }
  }

  if (this->input_file.eof()) {
    this->is_file_open = false;
    this->input_file.close();
  }
}

void VMParser::findInstruction() {
  commandType command = C_NOT_DEFINE;

  /*The command isn't a empty line*/

  vector<string> line_parsed = this->parseLine();

  if (line_parsed.empty()) {
    command = C_COMMENT;
  }

  auto command_find = commandTable.find(line_parsed[0]);

  if (command_find != commandTable.end()) {
    command = commandTable[line_parsed[0]];
    this->current_command = command;
    this->findArg1and2(line_parsed);

  } else {
    cerr << "line : " << this->getCurrentLine() << " --> wrong command..."
         << endl;
    return;
  }

}

void VMParser::findArg1and2(vector<string> line_parsed) {
  if (line_parsed.empty()) {
    cerr << "Error : empty line" << endl;
    return;
  }

  if (this->current_command == C_ARITHMETIC) {
    this->arg1 = line_parsed[0];
    this->arg2 = 0;
    return;
  }

  if (line_parsed.size() < 2 && this->current_command!=C_RETURN) {
    cerr << "Error: not enough arguments for command " << this->current_command
         << endl;
    return;
  }
  if(this->current_command == C_RETURN){
    this->arg1 = "";
    this->arg2 = 0;
  }
  if (this->current_command == C_PUSH || this->current_command == C_POP) {
    if (isValidSegment(line_parsed[1])) {
      this->arg1 = line_parsed[1];
    } else {
      cerr << line_parsed[1] << " is not a valid segment" << endl;
      return;
    }
  } else if (this->current_command == C_LABEL ||
             this->current_command == C_GOTO || this->current_command == C_IF ||
             this->current_command == C_FUNCTION ||
             this->current_command == C_CALL) {
    this->arg1 = line_parsed[1];
  }

  if ((this->current_command == C_PUSH || this->current_command == C_POP ||
       this->current_command == C_FUNCTION ||
       this->current_command == C_CALL) &&
      line_parsed.size() >= 3) {
    try {
      this->arg2 = stoi(line_parsed[2]);
    } catch (const invalid_argument &e) {
      cerr << "Error: not a number '" << line_parsed[2] << "'" << endl;
    } catch (const out_of_range &e) {
      cerr << "Error : out of range '" << line_parsed[2] << "'" << endl;
    }
  }
}