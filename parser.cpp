#include "parser.hpp"

Parser::Parser(const char* input_path):File(input_path),line_number(0){
    if(!File){
        cerr<<"Error when trying to open this file"<<endl;
    }
}

void Parser::readNextLine(){
    getline(this->File,this->current_line);
    this->line_number++;
}

int Parser::getLineNumber() const{
    return this->line_number;
}
string Parser::getCurrentLine() const{
    return this->current_line;
}

bool Parser::isOpen() const{
    return this->File.is_open();
}