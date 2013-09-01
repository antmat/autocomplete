#include "node.hpp"
#include <iostream>
#include <set>
namespace AC {
    Node* Node::search_internal(const String& phrase, unsigned int current_position, bool insert_on_miss, unsigned int freq) {
        assert(TOP_SUGGESTIONS_CNT >0);
        assert(current_position < phrase.size()+1);
        if(current_position == phrase.size()) {
            if(insert_on_miss) {
                this->frequency += freq;
            }
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
                search_node->top_node = search_node;
                this->subnodes.push_back(search_node);
            }
            else {
                return nullptr;
            }
        }
        Node* node_added = search_node->search_internal(phrase, current_position+1, insert_on_miss, freq);
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
            return this->subnodes[0]->search_internal(phrase, current_position, false);
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

    void Node::fill_suggests(std::vector<String>& suggests, unsigned int count) {
        auto comparator = [](Node* lhs, Node* rhs){
            if(lhs->frequency > rhs->frequency) {
                return true;
            }
            if(lhs->frequency < rhs->frequency) {
                return false;
            }
            return lhs < rhs;
        };
        std::map<Node*, Node*, decltype(comparator)> sorting_map(comparator);
        if(this->frequency>0) {
            sorting_map[this] = this;
        }
        for(unsigned int i=0; i< this->subnodes.size(); i++) {
            sorting_map[this->subnodes[i]->top_node] = this->subnodes[i];
        }

        //something like O(k*k*m+k*log(k)) where k -number of requested elements, m - average number of subnodes
        //if k const and m const O(1)
        for(unsigned int i=1; i<= count; i++) {
            auto it = sorting_map.end();
            if(it == sorting_map.begin()) {
                break;
            }
            it--;
            unsigned int min_frequency = it->first->frequency;

            for(auto& pair : sorting_map) {
                if(pair.first->frequency < min_frequency) {
                    break;
                }
                if(pair.second->frequency > min_frequency) {
                    sorting_map[pair.second] = pair.second;
                }
                auto& cur_subnodes = pair.second->subnodes;
                for(unsigned int k=0; k < cur_subnodes.size(); k++) {
                    if(cur_subnodes[k]->top_node->frequency > min_frequency ||
                       (sorting_map.size() < count && cur_subnodes[k]->top_node->frequency > 0)) {
                        sorting_map[cur_subnodes[k]->top_node] = cur_subnodes[k];
                    }
                    if(cur_subnodes[k]->frequency > min_frequency ||
                       (sorting_map.size() < count && cur_subnodes[k]->frequency > 0)) {
                        sorting_map[cur_subnodes[k]] = cur_subnodes[k];
                    }
                }
            }
            if(sorting_map.size() > count) {
                for(size_t k = sorting_map.size(); k>count; k--) {
                    auto it2 = sorting_map.end();
                    --it2;
                    sorting_map.erase(it2);
                }
            }
        }
        for(auto& pair : sorting_map) {
            suggests.push_back(pair.first->get_phrase());
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
