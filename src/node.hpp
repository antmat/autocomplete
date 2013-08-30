#ifndef NODE_HPP
#define NODE_HPP
#include <vector>
#include <string>
#include <map>
#include <assert.h>
#include "util/string.hpp"
#define TOP_SUGGESTIONS_CNT 20
namespace AC {
    class TreeConstIterator;
    class Node
    {
        friend class TreeConstIterator;
    public:
        typedef std::vector<Node*> Subnodes;
    protected:
        char value;
        Node* parent;
        Subnodes subnodes;
        unsigned int frequency; //TODO test with separate leaves. Now node can be considered as leaf if it has frequency >0
        Node* top_node;
        Node* search_internal(const String& phrase, unsigned int current_position, bool insert_on_miss, unsigned int freq = 1);
    public:
        inline unsigned int get_frequency() const{
            return this->frequency;
        }

        Node& operator=(const Node&) = delete;
        Node(const Node&) = delete;
        Node():
            value(0),
            parent(nullptr),
            subnodes(),
            frequency(0),
            top_node(this)
        {
        }
        ~Node() throw() {
            for(auto subnode : this->subnodes) {
                delete subnode;
            }
        }

        Node* search(const String& phrase, unsigned int current_position);
        Node* add_phrase(const String& phrase, unsigned int current_position, unsigned int freq = 1);
        void fill_suggests(std::vector<String>& suggests, unsigned int count, bool search_deeper = true);
        void fill_phrase (String& phrase) const;
        String get_phrase() const;
        void prune(unsigned int prunning_limit);
    };

}

#endif // NODE_HPP
