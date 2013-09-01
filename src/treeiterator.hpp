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
        /**
         * @brief Get iterator to tree begining
         * @param tree Tree to iterate.
         * @return iterator to tree begining
         */
        static TreeConstIterator begin(const Tree& tree);
        /**
         * @brief Get iterator to tree end
         * @param tree Tree to iterate.
         * @return iterator to tree end
         */
        static TreeConstIterator end(const Tree& tree);
        /**
         * @brief Construct iterator from tree node
         * @param _node
         */
        TreeConstIterator(Node* _node);
        TreeConstIterator(const TreeConstIterator& it);
        TreeConstIterator& operator++();
        //TODO add decrement operator
        bool operator==(const TreeConstIterator& rhs);
        bool operator!=(const TreeConstIterator& rhs);
        const Node& operator*();
    };
}
#endif // TREEITERATOR_HPP
