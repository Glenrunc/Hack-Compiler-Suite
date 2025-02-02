#include <iostream>
#include <unordered_map>
#include <string>
#include "parser.hpp"
using namespace std;
// Input file -> .asm,  Output file -> .hack (16 bits instructions by line refer to A-instruction, C-instruction, symbol like (LOOP))

unordered_map<string, int> LabelTable = {
     {"SP", 0x0000},  
     {"LCL", 0x0001},
     {"ARG", 0x0002},
     {"THIS", 0x0003},
     {"THAT", 0x0004},
     // Registres R0 à R15
     {"R0", 0x0000}, {"R1", 0x0001}, {"R2", 0x0002}, {"R3", 0x0003},
     {"R4", 0x0004}, {"R5", 0x0005}, {"R6", 0x0006}, {"R7", 0x0007},
     {"R8", 0x0008}, {"R9", 0x0009}, {"R10", 0x000A}, {"R11", 0x000B},
     {"R12", 0x000C}, {"R13", 0x000D}, {"R14", 0x000E}, {"R15", 0x000F},
     // Registres spéciaux
     {"SCREEN", 0x4000}, // Adresse de départ de l'écran
     {"KBD", 0x6000}     // Adresse du clavier
 };




int main(int argc, char* argv[]){

    Parser newParser("test.txt");
    newParser.readNextLine();

    cout<<newParser.getCurrentLine()<<endl;

    return EXIT_SUCCESS;
}