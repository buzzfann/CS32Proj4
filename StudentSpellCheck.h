#ifndef STUDENTSPELLCHECK_H_
#define STUDENTSPELLCHECK_H_

#include "SpellCheck.h"

#include <string>
#include <vector>
#include <set>

const int ALPHABET_SIZE_APOS = 27;

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
        Node* children[ALPHABET_SIZE_APOS];
        Node(char c)
        {
            this->c = c;
            isWord = false;
            for (int i = 0; i < ALPHABET_SIZE_APOS; i++)
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
    bool search(std::string word, Node* root);
    void deleteNodes(Node* root);
};

#endif  // STUDENTSPELLCHECK_H_
