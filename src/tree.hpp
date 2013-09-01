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

        /**
         * @brief Prune tree root and subnodes. Delete all phrases with frequency less than prunning_limit
         * @param prunning_limit
         */
        void prune(unsigned int prunning_limit);

        /**
         * @brief Erase the whole tree
         */
        void erase();

        /**
         * @brief Add phrase to a tree
         * @param phrase Phrase to add
         * @param frequency frequency to add with.
         */
        void add_phrase(const String& phrase, unsigned int frequency = 1);

        /**
         * @brief Fill array of suggests with most likely phrase continuations.
         * @param phrase Phrase to search
         * @param suggests Vector of suggests to fill.
         * @param count Maximum amount of suggests.
         */
        void fill_suggests(const String& phrase, std::vector<String>& suggests, unsigned int count);

        /**
         * @brief Same as fill_suggests but returns a copy. Use fill_suggests where possible.
         * @param phrase Phrase to search
         * @param count Maximum amount of suggests.
         * @return vector of suggests
         */
        std::vector<String> get_suggests(const String& phrase, unsigned int count);

        /**
         * @brief Return const iterator to tree begining
         * @return const iterator to tree begining
         */
        ConstIterator begin() const;

        /**
         * @brief Return const iterator to tree end
         * @return const iterator to tree end
         */
        ConstIterator end() const;
    };
}
#endif // TREE_HPP
