#include "tree.hpp"
#include "treeiterator.hpp"
#include "node.hpp"
namespace AC {
    Tree::Tree() :
        root(new Node())
    {
    }

    void Tree::add_phrase(const std::string& phrase) {
        this->root->add_phrase(phrase, 0);
    }

    void Tree::fill_suggests(const std::string& phrase, std::vector<std::string>& suggests) {
        assert(suggests.size() == 0);
        Node* phrase_node = this->root->search(phrase, 0);
        if(phrase_node == nullptr) {
            return;
        }
        phrase_node->fill_suggests(suggests);
    }

    std::vector<std::string> Tree::get_suggests(const std::string& phrase) {
        std::vector<std::string> result;
        this->fill_suggests(phrase, result);
        return result;
    }

    Tree::Iterator Tree::begin() {
        return Tree::Iterator::begin(*this);
    }

    Tree::Iterator Tree::end() {
        return Tree::Iterator::end(*this);
    }

    Tree::~Tree() throw() {
        delete (this->root);
    }

    void Tree::erase() {
        delete this->root;
    }
}
