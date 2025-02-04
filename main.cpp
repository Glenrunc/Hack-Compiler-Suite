#include "parser.hpp"
// Input file -> .asm,  Output file -> .hack (16 bits instructions by line refer
// to A-instruction, C-instruction, symbol like (LOOP))

int main(int argc, char* argv[]) {

  Parser parser = Parser("test.txt");

  while(parser.isOpen()){
    if(!(parser.getCurrentLine().empty())){
      parser.findInstruction();
      cout<<"line number"<< parser.getCurrentLineNumber()<<"  : "<<parser.getCurrentLine()<<" is a : "<< parser.getCurrentInstruction()<<endl;
    }
    parser.readNextLine();

  }


  return EXIT_SUCCESS;
}