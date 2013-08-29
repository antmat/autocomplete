#include "node.hpp"
#include <iostream>
namespace AC {

    Node* Node::search_internal(const std::string& phrase, unsigned int current_position, bool insert_on_miss) {
        assert(TOP_SUGGESTIONS_CNT >0);
        assert(current_position < phrase.size()+1);
        if(current_position == phrase.size()) {
            this->frequency++;
            //std::cout << "added " << this->get_phrase() << ", frequency: " << this->get_frequency() <<std::endl;
            return this;
        }
        Node* search_node = nullptr;
        for(auto subnode : this->subnodes) {
            if(subnode->value == phrase[current_position]) {
                search_node = subnode;
                break;
            }
        }
        if(search_node == nullptr) {
            if(insert_on_miss) {
                search_node = new Node();
                search_node->value = phrase[current_position];
                search_node->parent = this;
                this->subnodes.push_back(search_node);
            }
            else {
                return nullptr;
            }
        }
        Node* node_added = search_node->search_internal(phrase, current_position+1, insert_on_miss);
        if(node_added == nullptr) {
            return node_added;
        }
        if(this->top_node == nullptr) {
            this->top_node = node_added;
        }
        else if (node_added->frequency > this->top_node->frequency) {
            this->top_node = node_added;
        }
        return node_added;
    }

    Node* Node::search(const std::string& phrase, unsigned int current_position) {
        if(this->parent == nullptr) {
            if(this->subnodes.empty()) {
                return nullptr;
            }
            return this->subnodes[0]->search_internal(phrase, current_position, true);
        }
        return this->search_internal(phrase, current_position, false);
    }

    Node* Node::add_phrase(const std::string& phrase, unsigned int current_position) {
        if(this->parent == nullptr) {
            if(this->subnodes.empty()) {
                this->subnodes.push_back(new Node());
                this->subnodes[0]->parent = this;
            }
            return this->subnodes[0]->search_internal(phrase, current_position, true);
        }
        return this->search_internal(phrase, current_position, true);
    }

    void Node::fill_suggests(std::vector<std::string>& /*suggests*/) {
        /*for(unsigned int i=0; i<TOP_SUGGESTIONS_CNT; i++) {
            if(this->top_nodes[i] != nullptr) {
                suggests.push_back(this->top_nodes[i]->get_phrase());
            }
            else {
                break;
            }
        }*/
    }

    void Node::fill_phrase (std::string& phrase) {
        if(this->parent != nullptr) {
            this->parent->fill_phrase(phrase);
        }
        phrase += value;
    }

    std::string Node::get_phrase() {
        std::string phrase;
        this->fill_phrase(phrase);
        return phrase;
    }

}
