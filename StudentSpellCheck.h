#ifndef STUDENTSPELLCHECK_H_
#define STUDENTSPELLCHECK_H_

#include "SpellCheck.h"

#include <string>
#include <vector>
#include <set>

const int ALPHABET_SIZE = 26;

class StudentSpellCheck : public SpellCheck {
public:
    StudentSpellCheck()
    {
        m_trie = new Trie();
    }
	virtual ~StudentSpellCheck();
	bool load(std::string dict_file);
	bool spellCheck(std::string word, int maxSuggestions, std::vector<std::string>& suggestions);
	void spellCheckLine(const std::string& line, std::vector<Position>& problems);

private:

    class Node
    {
    public:
        char c;
        bool isWord;
        Node* children[ALPHABET_SIZE];
        Node(char c)
        {
            this->c = c;
            isWord = false;
            for (int i = 0; i < ALPHABET_SIZE; i++)
            {
                this->children[i] = nullptr;
            }
        }
    };
    
    class Trie
    {
    public:
//        Trie* children[ALPHABET_SIZE];
        Trie()
        {
            m_root = new Node('\0');
        }
        Node* getRoot() {return m_root;}
//        void insert(std::string str);
//        bool search(std::string str);
        
    private:
        Node* m_root;
    };
    
    Trie* m_trie;
    std::set<std::string> dictSet;
    
//    void insert(std::string str)
//    {
//        // start at root
//        Trie* curr = &m_trie;
//        for (int i = 0; i < str.length(); i++)
//        {
//            if (curr->children[str[i]] == nullptr)
//            {
//                // create new node
//                curr->children[str[i]] = new Trie();
//            }
//
//            // go to next node
//            curr = curr->children[str[i]];
//        }
//
//        // mark the current node as a leaf
////        curr->isLeaf = true;
//    }
};

#endif  // STUDENTSPELLCHECK_H_
