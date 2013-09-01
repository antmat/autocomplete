#include "util/string.hpp"
#include "preprocessor.hpp"

using namespace AC;
int main (int argc, const char **argv) {
    if(argc != 3) {
        std::cerr << "Usage ./loader [infile] [outfile]" << std::endl;
        exit(1);
    }
    String infile(argv[1]), outfile(argv[2]);
    unsigned int chunks_created = 0;
    Preprocessor::compact_data(infile, outfile, chunks_created);
    Preprocessor::merge_data(outfile, chunks_created);
}
