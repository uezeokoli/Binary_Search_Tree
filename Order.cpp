// /****************************************************************************************
// *  Order.cpp
// *  Constructs Dictionary from input file and outputs the inorder and preoder representation in output file
// *****************************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include <fstream>
#include"Dictionary.h"

using namespace std;

int main(int argc, char *argv[]){
    if (argc != 3){
        fprintf(stderr, "Invalid number of command line arguments\n");
        exit(EXIT_FAILURE);
    }
    Dictionary D;
    int line_num = 1;
    string outfile_name =  argv[2];
    ifstream infile;
    infile.open(argv[1]);
    ofstream outfile;             
    outfile.open(outfile_name);

    string line;
    getline(infile,line);
    while (!infile.eof()){
        D.setValue(line,line_num++);
        getline(infile,line);
    }

    outfile<< D << endl;
    outfile<< D.pre_string();

    outfile.close();
    infile.close();
}
