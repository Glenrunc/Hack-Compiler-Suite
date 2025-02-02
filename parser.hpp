#include <fstream>
#include <iostream>
#include <string>

enum CommandType { A_COMMAND = 0, C_COMMAND = 1, L_COMMAND = 2};
using namespace std;

class Parser {
 private:
  ifstream File;
  int line_number;
  string current_line;
  bool isFileOpen;
  CommandType currentCommand;

 public:
  Parser() : line_number(0) {};
  Parser(const char* input_path);
  virtual ~Parser() {};

  void readNextLine();
  int getLineNumber() const;
  string getCurrentLine() const;
  CommandType getCurrentCommand() const;
  bool isOpen() const;
};
