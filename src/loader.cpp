#include <string>
#include "preprocessor.hpp"
int main (int argc, const char **argv) {
    if(argc != 3) {
        std::cerr << "Usage ./loader [infile] [outfile]" << std::endl;
        exit(1);
    }
    std::string infile(argv[1]), outfile(argv[2]);
    AC::Preprocessor::compact_data(infile, outfile);
}
