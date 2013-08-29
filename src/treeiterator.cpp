#include "treeiterator.hpp"
#include <iostream>
namespace AC {
    TreeConstIterator TreeConstIterator::begin(const Tree& tree) {

        if(tree.root->subnodes.empty()) {
            return TreeConstIterator(tree.root);
        }
        assert(tree.root->subnodes[0] != nullptr);
        return TreeConstIterator(tree.root->subnodes[0]);
    }

    TreeConstIterator TreeConstIterator::end(const Tree& tree) {
        return TreeConstIterator(tree.root);
    }

    TreeConstIterator::TreeConstIterator(Node* _node) :
        node(_node)
    {}

    TreeConstIterator::TreeConstIterator(const TreeConstIterator& it) :
        node(it.node)
    {}

    //Todo decrement iterator, reverse iterator.
    TreeConstIterator& TreeConstIterator::operator++() {
        if(!this->node->subnodes.empty()) {
            this->node = this->node->subnodes[0];
            return *this;
        }
        while(this->node->parent != nullptr) {
            char value = this->node->value;
            this->node = this->node->parent;
            unsigned int i;
            for(i = 0; i<this->node->subnodes.size(); i++) {
                if(this->node->subnodes[i]->value == value) {
                    break;
                }
            }
            assert(i < this->node->subnodes.size());
            i++;
            if(i < this->node->subnodes.size()) {
                this->node = this->node->subnodes[i];
                return *this;
            }
        }
        return *this;
    }
    bool TreeConstIterator::operator==(const TreeConstIterator& rhs) {
        return this->node==rhs.node;
    }
    bool TreeConstIterator::operator!=(const TreeConstIterator& rhs) {
        return this->node!=rhs.node;
    }
    const Node& TreeConstIterator::operator*() {
        return *node;
    }
}
