#ifndef TREE_HPP
#define TREE_HPP
#include "util/string.hpp"
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

        void prune(unsigned int prunning_limit);
        void erase();
        void add_phrase(const String& phrase, unsigned int frequency = 1);
        void fill_suggests(const String& phrase, std::vector<String>& suggests, unsigned int count);
        std::vector<String> get_suggests(const String& phrase, unsigned int count);
        ConstIterator begin() const;
        ConstIterator end() const;
    };
}
#endif // TREE_HPP
