#ifndef NODE_HPP
#define NODE_HPP
#include <vector>
#include <string>
#include <map>
#include <assert.h>
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
        Node* search_internal(const std::string& phrase, unsigned int current_position, bool insert_on_miss);
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
            top_node(nullptr)
        {
        }
        ~Node() throw() {
            for(auto subnode : this->subnodes) {
                delete subnode;
            }
        }

        Node* search(const std::string& phrase, unsigned int current_position);
        Node* add_phrase(const std::string& phrase, unsigned int current_position);
        void fill_suggests(std::vector<std::string>& suggests);
        void fill_phrase (std::string& phrase) const;
        std::string get_phrase() const;
    };

}

#endif // NODE_HPP
