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
        /**
         * @brief value of a node.
         */
        char value;
        /**
         * @brief link to parent node. Basically needed to retrieve the whole word.
         */
        Node* parent;
        /**
         * @brief vector of pointers to subnodes
         */
        Subnodes subnodes;

        /**
         * @brief frequency of a word, which this node contains.
         */
        unsigned int frequency; //TODO test with separate leaves. Now node can be considered as leaf if it has frequency >0

        /**
         * @brief
         */
        Node* top_node;

        /**
         * @brief internal search and optional insert routine
         * @param phrase Phrase to search
         * @param current_position current level of a tree and position of char in phrase.
         * @param insert_on_miss Should we insert new node if we could not find one or should we increase frequency counter if found one
         * @param freq only applicable if insert_on_miss is true. frequency of inserting node(default 1)
         * @return inserted or found node (nullptr if insert_on_miss is false and node was not found)
         */
        Node* search_internal(const String& phrase, unsigned int current_position, bool insert_on_miss, unsigned int freq = 1);
    public:
        /**
         * @brief get frequency of a word corrsaponding to node
         * @return
         */
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

        /**
         * @brief interface method for recursive searching phrase in the tree
         * @param phrase Phrase to search
         * @param current_position Current level of a tree and position of char in phrase.
         * @return found node or nullptr
         */
        Node* search(const String& phrase, unsigned int current_position);

        /**
         * @brief interface method for adding node or increasing frequncy of existing node.
         * @param phrase Phrase to add
         * @param current_position Current level of a tree and position of char in phrase.
         * @param freq Frequency to set or add to existing node.
         * @return Node inserted
         */
        Node* add_phrase(const String& phrase, unsigned int current_position, unsigned int freq = 1);

        /**
         * @brief Fill suggests ith most frequent nodes in sub tree of a phrase.
         * @param suggests Suggests to be filled
         * @param count maximum number of suggests
         */
        void fill_suggests(std::vector<String>& suggests, unsigned int count);

        /**
         * @brief fill phrase with word which node contains. Contents of a phrase are overwritten
         * @param phrase Phrase to write into
         */
        void fill_phrase (String& phrase) const;

        /**
         * @brief same goal as fill phrase but phrase is returned(copying overhead)
         * @return
         */
        String get_phrase() const;

        /**
         * @brief prune node and subnodes. Delete all phrases with frequency less than prunning_limit
         * @param prunning_limit
         */
        void prune(unsigned int prunning_limit);
    };

}

#endif // NODE_HPP
