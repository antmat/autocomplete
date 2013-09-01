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
        /**
         * @brief read chunk of preprocessed data to map of phrase:frequency of a phrase
         * @param input Input stream
         * @param count maximum amount of lines to read
         * @param phrase_counts map to fill
         */
        void read_chunk(std::ifstream& input, unsigned int count, std::map<String, unsigned int>& phrase_counts);
        /**
         * @brief save Tree to a data chunk on fs
         * @param tree Tree to save.
         * @param chunk_num current number of chunk(suffix to file base name)
         * @param outfile_base_name Base name of a file used to write chunk
         */
        void save_chunk(const Tree& tree, unsigned int chunk_num, const String& outfile_base_name);

        /**
         * @brief Read one line from input
         * @param input Input stream
         * @param data String to read in. Data is overwritten
         * @param frequency uint to read in frequency of read phrase.
         * @return true on success, false otherwise
         */
        bool read_string(std::ifstream& input, String& data, unsigned int& frequency);

        /**
         * @brief Find a stream containing lesser phrase according to default string comparision.
         * @param streams Streams to choose from
         * @param min_phrase String to write in lesser phrase. Contents overwritten.
         * @param phrase_counts Map to write in read data for streams in order not to loose it or write back.
         * @return index of a stream containing lesser phrase
         */
        int determine_min_stream(std::vector<std::shared_ptr<std::ifstream>>& streams, String& min_phrase, std::map<String, unsigned int>& phrase_counts);

        /**
         * @brief Save a fragment of data to main merged file of data.
         * @param outfile_name Name of a file
         * @param phrase_counts Phrases with their counts
         * @param min_phrase minimum phrase of current open streams. We don't write in output files phrases bigger than this one.
         * @param finalize true if all streams were succesefully read to the end and we should write all data.
         */
        void swap_phrases(const String& outfile_name, std::map<String, unsigned int>& phrase_counts, const String& min_phrase, bool finalize = false);

        /**
         * @brief Merge chunks of data containig of chunk_base_name+"."+(for one to chunks_count) to one sorted output file.
         * @param chunk_base_name base name of a chunk filename
         * @param chunks_count Amount of chunks
         */
        void merge_data(const String& chunk_base_name, unsigned int chunks_count);

        /**
         * @brief Compact data from raw queries to bunch of chunk files with query:frequency structure.
         * @param infile Input file name
         * @param outfile_base_name Output file name
         * @param chunks_created In this var number of chunks actually created is written
         * @return true on success, false otherwise.
         */
        bool compact_data(const String& infile, const String& outfile_base_name, unsigned int& chunks_created);
        /**
         * @brief Load prefix tree from a file. Tree is being prunned according to desired memory consumption
         * @param tree Tree to write in
         * @param infile Input file name
         */
        void load_tree(Tree& tree, const String& infile);
    }
}
#endif
