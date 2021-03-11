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
    // define node class
    class Node
    {
    public:
        char c;
        bool isWord;
        // alphabet size apos is alphabet + apostrophe = 27
        // used arrays
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
    // define Trie class
    class Trie
    {
    public:
        Trie()
        {
            m_root = new Node('\0');    // null byte
        }
        Node* getRoot() {return m_root;}
        
    private:
        Node* m_root;
    };
    
    Trie* m_trie;
    bool search(std::string word, Node* root); // search for word in dictionary
    void deleteNodes(Node* root);               // destructor helper
};

#endif  // STUDENTSPELLCHECK_H_
