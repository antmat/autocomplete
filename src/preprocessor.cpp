#include "preprocessor.hpp"
#include "memusage.hpp"
#include <stdexcept>
#include "util/string.hpp"
//TODO move to constants file and replace macro to const vars
#ifndef TEST_MEM_EACH
    #define TEST_MEM_EACH 100000
#endif

#ifndef MAX_ALLOWED_MEM
    #define MAX_ALLOWED_MEM 2000000
#endif

#ifndef MERGE_CHUNK_SIZE
    #define MERGE_CHUNK_SIZE 10000
#endif

namespace AC {
    namespace Preprocessor {

        void save_chunk(const Tree& tree, unsigned int chunk_num, const String& outfile_base_name) {
            std::ofstream output(outfile_base_name+'.'+std::to_string(chunk_num), std::ifstream::out);
            if(!output.is_open()) {
                std::cerr << "Could not open " << outfile_base_name+'.'+std::to_string(chunk_num) << " for writing" << std::endl;
                return;
            }

            for(const auto& element : tree) {
                if(element.get_frequency()>0) {
                    String phrase(element.get_phrase()+":"+std::to_string(element.get_frequency())+'\n');
                    output.write(phrase.c_str(), phrase.size());
                }
            }
        }

        void read_chunk(std::ifstream& input, unsigned int count, std::map<String, unsigned int>& phrase_counts) {
            for(unsigned int i=0; i < count; i++) {
                String data;
                unsigned int frequency;
                if(read_string(input, data, frequency)) {
                    phrase_counts[data] += frequency;
                }
                else {
                    break;
                }
            }
        }

        bool read_string(std::ifstream& input, String& data, unsigned int& frequency) {
            frequency = 0;
            if(!std::getline(input, data)) {
                return false;
            }
            if(data.size() == 0) {
                return true;
            }
            size_t colon_position = data.find_last_of(':');
            frequency = std::stoi(data.substr(colon_position+1));
            data.erase(colon_position);
            return true;
        }

        int determine_min_stream(std::vector<std::shared_ptr<std::ifstream>>& streams, String& min_phrase, std::map<String, unsigned int>& phrase_counts) {
            min_phrase = "";
            if(streams.size() == 0) {
                std::cout << "streams size is " << streams.size() << std::endl;
                throw std::logic_error("streams are empty");
            }
            String data;
            unsigned int frequency;
            int stream_index = -1;
            for(unsigned int i=0; i < streams.size(); i++) {
                if(read_string(*(streams[i]), data, frequency)) {
                    if(data ==  "") {
                        throw std::logic_error("empty data read");
                    }
                    phrase_counts[data] = frequency;
                    if(min_phrase == "") {
                        min_phrase = data;
                        stream_index = i;
                    }
                    else if(data <min_phrase) {
                        min_phrase = data;
                        stream_index = i;
                    }
                }
            }
            return stream_index;
        }

        void swap_phrases(const String& outfile_name, std::map<String, unsigned int>& phrase_counts, const String& min_phrase, bool finalize) {
            std::map<String, unsigned int>::iterator it;
            std::ofstream output(outfile_name, std::ios::app);
            for(it = phrase_counts.begin(); it != phrase_counts.end(); it++) {
                if(!finalize && it->first > min_phrase) {
                    assert(it != phrase_counts.begin());
                    break;
                }
                output << it->first << ":" << it->second << "\n";
            }
            phrase_counts.erase(phrase_counts.begin(), it);
        }

        void merge_data(const String& chunk_base_name, unsigned int chunks_count) {
            remove(chunk_base_name.c_str());
            std::vector<std::shared_ptr<std::ifstream>> streams;
            std::map<String, unsigned int> phrase_counts;
            String min_phrase;
            String min_phrase_stream_index;
            assert(chunks_count>0);
            for(unsigned int i = 0; i < chunks_count; i++) {
                streams.push_back(std::make_shared<std::ifstream>(chunk_base_name+'.'+std::to_string(i))); //todo move to get_file_name function
            }

            int index;
            unsigned int read_chunks = 0;
            while((index = determine_min_stream(streams, min_phrase, phrase_counts)) != -1)
            {
                read_chunk(*(streams[index]), MERGE_CHUNK_SIZE, phrase_counts);
                read_chunks++;
                if(read_chunks % chunks_count == 0)
                {
                    swap_phrases(chunk_base_name, phrase_counts, min_phrase);
                }
            }
            swap_phrases(chunk_base_name, phrase_counts, min_phrase, true);
        }

        bool compact_data(const String& infile, const String& outfile_base_name, unsigned int& chunks_created) {
            std::cout << "Parsing " << infile << std::endl;
            std::ifstream input(infile);
            if(!input.is_open()) {
                std::cerr << "Could not open " << infile << " for reading" << std::endl;
                return false;
            }
            Tree tree;
            unsigned int cnt = 0;
            chunks_created = 0;
            unsigned int mem_usage_vm = 0, mem_usage_resident = 0;
            for (String data; std::getline(input, data); )
            {
                if(data.size() == 0) {
                    continue;
                }
                if(++cnt % TEST_MEM_EACH == 0) {
                    process_mem_usage(mem_usage_vm, mem_usage_resident);
                    if(mem_usage_resident > MAX_ALLOWED_MEM) {
                        Preprocessor::save_chunk(tree, chunks_created++, outfile_base_name);
                        tree.erase();
                    }
                }
                /*
                size_t tab_position = data.find_first_of('\t');
                if(tab_position == data.size()-1) {
                    std::cerr << "Bad input data format. Found last \\t in string - " << data << std::endl;
                    return false;
                }
                if(tab_position != String::npos) {
                    data.erase(0, tab_position+1);
                }
                */
                tree.add_phrase(data);
            }
            Preprocessor::save_chunk(tree, chunks_created++, outfile_base_name);
            tree.erase();
            std::cout <<"compacted to " << chunks_created << " chunks" << std::endl;
            return true;
        }
        void load_tree(Tree& tree, const String& infile) {

            std::ifstream input(infile);
            std::cerr << "Loading data from " << infile <<std::endl;
            unsigned int frequency;
            String data;
            unsigned int cnt = 0;
            unsigned int prunning_limit = 0;
            unsigned int mem_usage_vm = 0, mem_usage_resident = 0;
            while(read_string(input, data, frequency)){
                tree.add_phrase(data, frequency);
                if(++cnt % TEST_MEM_EACH == 0) {
                    process_mem_usage(mem_usage_vm, mem_usage_resident);
                    if(mem_usage_resident > MAX_ALLOWED_MEM) {
                        tree.prune(++prunning_limit);
                    }
                }
            }
        }
    }
}
