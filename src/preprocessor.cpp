#include "preprocessor.hpp"
#include "memusage.hpp"
#ifndef TEST_MEM_EACH
    #define TEST_MEM_EACH 100000
#endif
#ifndef MAX_ALLOWED_MEM
    #define MAX_ALLOWED_MEM 2000000
#endif
namespace AC {
    namespace Preprocessor {
        void save_chunk(const Tree& tree, unsigned int chunk_num) {
            for(auto& element : tree) {
                if(element.get_frequency()>0) {
                    std::string phrase(element.get_phrase()+":"+std::to_string(element.get_frequency())+'\n');
                    output.write(phrase.c_str(), phrase.size());
                }
            }
            tree = Tree();
        }

        bool compact_data(const std::string& infile, const std::string& outfile) {

            std::cout << "Parsing " << infile << " to " << outfile << std::endl;
            std::ifstream input(infile);
            if(!input.is_open()) {
                std::cerr << "Could not open " << infile << " for reading" << std::endl;
                return false;
            }
            std::ofstream output(outfile,std::ifstream::out);
            if(!output.is_open()) {
                std::cerr << "Could not open " << outfile << " for writing" << std::endl;
                return false;
            }

            Tree tree;
            unsigned int chunk_num = 0;
            unsigned int cnt = 0;
            unsigned int mem_usage_vm = 0, mem_usage_resident = 0;
            for (std::string data; std::getline(input, data); )
            {
                if(data.size() == 0) {
                    continue;
                }
                if(++cnt % TEST_MEM_EACH == 0) {
                    process_mem_usage(mem_usage_vm, mem_usage_resident);
                    if(mem_usage_resident > MAX_ALLOWED_MEM) {
                        Preprocessor::save_chunk(tree, ++chunk_num);
                    }
                }
                /*
                size_t tab_position = data.find_first_of('\t');
                if(tab_position == data.size()-1) {
                    std::cerr << "Bad input data format. Found last \\t in string - " << data << std::endl;
                    return false;
                }
                if(tab_position != std::string::npos) {
                    data.erase(0, tab_position+1);
                }
                */
                tree.add_phrase(data);
            }


            return true;
        }
    }
}
