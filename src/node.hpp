#ifndef NODE_HPP
#define NODE_HPP
#include <vector>
#include <string>
#include <map>
#include <array>
#include <assert.h>
#define TOP_SUGGESTIONS_CNT 20
namespace AC {
    class Node
    {
    protected:
        char value;
        Node* parent;
        std::map<char, Node*> subnodes; //TODO test with vector. Vector should slow down search and reduce memory consumption with large number of subnodes. In the opposite on low number of subnodes -map is better.
        unsigned int frequency; //TODO test with separate leaves. Now node can be considered as leaf if it has frequency >0
        std::array<Node*, TOP_SUGGESTIONS_CNT> top_nodes; //If we really care about 8 bytes we can use C array
        Node* search_internal(const std::string& phrase, unsigned char current_position, bool insert_on_miss) {
            assert(TOP_SUGGESTIONS_CNT >0);
            assert(current_position >=0);
            assert(current_position < phrase.size()+1);
            if(current_position == phrase.size()) {
                this->frequency++;
                return this;
            }
            if(this->subnodes[phrase[current_position]] == nullptr) {
                if(insert_on_miss) {
                    Node* new_node = new Node();
                    new_node->value = phrase[current_position];
                    new_node->parent = this;
                    this->subnodes[phrase[current_position]] = new_node;
                }
                else {
                    return nullptr;
                }
            }
            const Node* node_added = this->subnodes[phrase[current_position]]->search_internal(phrase, current_position+1, insert_on_miss);
            if(node_added == nullptr) {
                return node_added;
            }
            for(unsigned int i = 0; i< TOP_SUGGESTIONS_CNT; i++) {
                Node* node = this->top_nodes[i];
                if(node == nullptr) {
                    this->top_nodes[i] = node;
                    break;
                }
                assert(node != nullptr);
                if (node_added->frequency > node->frequency) {
                    for (unsigned int k = TOP_SUGGESTIONS_CNT -1; k > i; k--) {
                        this->top_nodes[k] = this->top_nodes[k-1];
                    }
                    this->top_nodes[i] = node_added;
                    break;
                }
            }
            return node_added;
        }

    public:
        Node():
            value(0),
            parent(nullptr),
            subnodes(),
            frequency(0),
            top_nodes()
        {
            top_nodes.fill(nullptr);
        }
        ~Node() throw() {
            for(auto& ptr_pair : this->subnodes) {
                delete ptr_pair.second;
            }
        }
        Node* search(const std::string& phrase, unsigned char current_position) {
            return this->search_internal(phrase, current_position, false);
        }

        Node* add_phrase(const std::string& phrase, unsigned char current_position) {
            return this->search_internal(phrase, current_position, true);
        }
        void fill_suggests(std::vector<std::string>& suggests) {
            for(unsigned int i=0; i<TOP_SUGGESTIONS_CNT; i++) {
                if(this->top_nodes[i] != nullptr) {
                    suggests.push_back(this->top_nodes[i].get_text());
                }
                else {
                    break;
                }
            }
        }
        void fill_phrase (std::string& phrase) {
            if(this->parent != nullptr) {
                this->parent->fill_phrase(phrase);
            }
            phrase += value;
        }

        std::string get_phrase() {
            std::string phrase;
            this->fill_phrase(phrase);
            return phrase;
        }
    };

}

#endif // NODE_HPP
