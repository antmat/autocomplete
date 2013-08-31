#ifndef PREPROCESSOR_HPP
#define PREPROCESSOR_HPP
#include <fstream>
#include <iostream>
#include "tree.hpp"

#ifdef __MACH__
#include <tr1/memory>
#else
#include <memory>
#endif




namespace AC {
    namespace Preprocessor {
        void read_chunk(std::ifstream& input, unsigned int count, std::map<String, unsigned int>& phrase_counts);
        void save_chunk(const Tree& tree, unsigned int chunk_num, const String& outfile_base_name);
        bool read_string(std::ifstream& input, String& data, unsigned int& frequency);
        int determine_min_stream(std::vector<std::shared_ptr<std::ifstream>>& streams, String& min_phrase, std::map<String, unsigned int>& phrase_counts);
        void swap_phrases(const String& outfile_name, std::map<String, unsigned int>& phrase_counts, const String& min_phrase, bool finalize = false);
        void merge_data(const String& chunk_base_name, unsigned int chunks_count);
        bool compact_data(const String& infile, const String& outfile_base_name, unsigned int& chunks_created);
        void load_tree(Tree& tree, const String& infile);
    }
}
#endif
