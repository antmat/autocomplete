#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
namespace AC {
    class Tree {
    protected:
        Node* root;
    public:
        inline Tree() throw() {
            this->root = new Node();
        }

        inline ~Tree() throw() {
            delete this->root;
        }

        inline add_phrase(const std::string& phrase) {
            this->root->add_phrase(phrase, 0);
        }
        void fill_suggests(const std::string& phrase, std::vector<std::string>& suggests) {
            assert(suggests.size() == 0);
            Node* phrase_node = this->root->search(phrase);
            if(phrase_node == nullptr) {
                return;
            }
            phrase_node->fill_suggests(suggests);
        }
        inline std::vector<std::string> get_suggests(const std::string& phrase) {
            std::vector<std::string> result;
            this->fill_suggests(phrase, result);
            return result;
        }

    };
}
#endif // TREE_HPP
