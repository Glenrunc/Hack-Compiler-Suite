#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class Parser{
    private:
        ifstream File;
        int line_number;
        string current_line;

    public:
        Parser(): line_number(0) {};
        Parser(const char* input_path);
        virtual ~Parser(){};


        void readNextLine();
        int getLineNumber() const;
        string getCurrentLine() const;
        bool isOpen() const;

};

