#ifndef TREEITERATOR_HPP
#define TREEITERATOR_HPP
#include "node.hpp"
#include "tree.hpp"
namespace AC {
    class Tree;
    class TreeConstIterator {
    private:
        Node* node;
    public:
        static TreeConstIterator begin(const Tree& tree);
        static TreeConstIterator end(const Tree& tree);
        TreeConstIterator(Node* _node);
        TreeConstIterator(const TreeConstIterator& it);
        TreeConstIterator& operator++();
        bool operator==(const TreeConstIterator& rhs);
        bool operator!=(const TreeConstIterator& rhs);
        Node& operator*();
    };
}
#endif // TREEITERATOR_HPP
