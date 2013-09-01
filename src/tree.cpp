#include "tree.hpp"
#include "treeiterator.hpp"
#include "node.hpp"
#include "util/string.hpp"
#include <iostream>
#include "constants.hpp"
namespace AC {
    Tree::Tree() :
        root(new Node())
    {
    }

    void Tree::add_phrase(const String& phrase, unsigned int frequency) {
        if(phrase.size() > MAX_PHRASE_SIZE) {
            return;
        }
        this->root->add_phrase(phrase, 0, frequency);
    }

    void Tree::fill_suggests(const String& phrase, std::vector<String>& suggests, unsigned int count) {
        if(phrase.size() == 0) {
            std::cerr << "phrase is empty" << std::endl;
            return;
        }
        assert(suggests.size() == 0);
        Node* phrase_node = this->root->search(phrase, 0);
        if(phrase_node == nullptr) {
            return;
        }
        phrase_node->fill_suggests(suggests, count);
    }

    std::vector<String> Tree::get_suggests(const String& phrase, unsigned int count) {
        std::vector<String> result;
        this->fill_suggests(phrase, result, count);
        return result;
    }

    Tree::ConstIterator Tree::begin() const {
        return Tree::ConstIterator::begin(*this);
    }

    Tree::ConstIterator Tree::end() const {
        return Tree::ConstIterator::end(*this);
    }

    Tree::~Tree() throw() {
        delete (this->root);
    }

    void Tree::erase() {
        delete this->root;
        this->root = new Node();
    }

    void Tree::prune(unsigned int prunning_limit) {
        std::cerr << "prunning tree with limit " << prunning_limit << std::endl;
        this->root->prune(prunning_limit);
    }
}
