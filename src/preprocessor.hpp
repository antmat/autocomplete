#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP
#include <fstream>
#include <iostream>
#include "tree.hpp"

#ifndef MAX_LINE_SIZE
    #define MAX_LINE_SIZE 256
#endif

namespace AC {
    namespace Preprocessor {
        bool compact_data(const std::string& infile, const std::string& outfile);
    }
}
#endif
