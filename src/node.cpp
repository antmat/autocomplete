#include "node.hpp"
#include <iostream>
namespace AC {

    Node* Node::search_internal(const String& phrase, unsigned int current_position, bool insert_on_miss, unsigned int freq) {
        assert(TOP_SUGGESTIONS_CNT >0);
        assert(current_position < phrase.size()+1);
        if(current_position == phrase.size()) {
            this->frequency += freq;
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

    Node* Node::search(const String& phrase, unsigned int current_position) {
        if(this->parent == nullptr) {
            if(this->subnodes.empty()) {
                return nullptr;
            }
            return this->subnodes[0]->search_internal(phrase, current_position, true);
        }
        return this->search_internal(phrase, current_position, false);
    }

    Node* Node::add_phrase(const String& phrase, unsigned int current_position, unsigned int freq) {
        if(this->parent == nullptr) {
            if(this->subnodes.empty()) {
                this->subnodes.push_back(new Node());
                this->subnodes[0]->parent = this;
            }
            return this->subnodes[0]->search_internal(phrase, current_position, true, freq);
        }
        return this->search_internal(phrase, current_position, true, freq);
    }

    void Node::fill_suggests(std::vector<String>& suggests, unsigned int count, bool search_deeper) {
        suggests.push_back(this->top_node->get_phrase());
        if(suggests.size() >= count) {
            return;
        }
        unsigned int limit = search_deeper ? 1 : this->top_node->frequency;
        for(unsigned int current_frequency = this->top_node->frequency; current_frequency>=limit; current_frequency--) {
            for(unsigned int i=0; i < this->subnodes.size(); i++) {
                if(this->subnodes[i]->top_node->frequency == current_frequency) {
                    this->subnodes[i]->fill_suggests(suggests, false);
                    if(suggests.size() >= count) {
                        return;
                    }
                }
            }
        }
    }

    void Node::fill_phrase (String& phrase) const {
        if(this->parent != nullptr && this->parent->parent != nullptr) {
            this->parent->fill_phrase(phrase);
            phrase += this->value;
        }
    }

    String Node::get_phrase() const {
        String phrase;
        this->fill_phrase(phrase);
        return phrase;
    }

    void Node::prune(unsigned int prunning_limit) {
        for(unsigned int i=0; i<this->subnodes.size(); i++) {
            if(this->subnodes[i]->top_node->frequency <= prunning_limit) {
                delete subnodes[i];
                this->subnodes.erase(this->subnodes.begin() + i);
                i--;
            }
            else {
                this->subnodes[i]->prune(prunning_limit);
            }
        }
    }

}
