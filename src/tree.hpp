#ifndef TREE_HPP
#define TREE_HPP
#include <string>
#include <vector>
#include "treeiterator.hpp"
namespace AC {
    class Node;
    class Tree {
    public:
        friend class TreeConstIterator;
        typedef TreeConstIterator ConstIterator;

    protected:
        Node* root;
    public:
        Tree& operator=(const Tree&) = delete;
        Tree(const Tree&) = delete;
        Tree();
        ~Tree() throw();

        void erase();
        void add_phrase(const std::string& phrase);
        void fill_suggests(const std::string& phrase, std::vector<std::string>& suggests);
        std::vector<std::string> get_suggests(const std::string& phrase);
        ConstIterator begin();
        ConstIterator end();
    };
}
#endif // TREE_HPP
