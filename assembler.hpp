#ifndef ASSEMBLER_HPP
#define ASSEMBLER_HPP

#include "parser.hpp"


class Assembler{
    private:
    Parser parser;
    string input_path;
    string output_path;
    ofstream output_file;

    public:
    Assembler(): parser(Parser()),input_path(string('\0')),output_path(string('\0')){};
    Assembler(string input_path, string output_path);
    virtual ~Assembler();


};
#endif