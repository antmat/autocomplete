#include "treeiterator.hpp"
#include <climits>
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
            Node* new_node(this->node->subnodes[0]);
            for(unsigned int i = 0; i<this->node->subnodes.size(); i++) {
                if(this->node->subnodes[i]->value < new_node->value) {
                    new_node = this->node->subnodes[i];
                }
            }
            this->node = new_node;
            return *this;
        }
        while(this->node->parent != nullptr) {
            char value = this->node->value;
            this->node = this->node->parent;
            unsigned int i;
            Node* new_node(nullptr);
            for(i = 0; i<this->node->subnodes.size(); i++) {
                if(this->node->subnodes[i]->value > value && (new_node == nullptr || this->node->subnodes[i]->value <= new_node->value)) {
                    new_node = this->node->subnodes[i];
                }
            }
            if(new_node != nullptr) {
                this->node = new_node;
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
