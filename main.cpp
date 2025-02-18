#include "assembler.hpp"
// Input file -> .asm,  Output file -> .hack (16 bits instructions by line refer
// to A-instruction, C-instruction, symbol like (LOOP))

int main(int argc, char *argv[]) {

  Assembler assembler = Assembler("test.asm", "test.hack");

  assembler.runAssembler();

  return EXIT_SUCCESS;
}