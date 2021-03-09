#include "StudentSpellCheck.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

///Users/buzzfann/Downloads/Wurd/Wurd/warandpeace.txt

const int APOSTROPHE = 39;
SpellCheck* createSpellCheck()
{
	return new StudentSpellCheck;
}

StudentSpellCheck::~StudentSpellCheck() {
	// TODO
}

bool StudentSpellCheck::load(std::string dictionaryFile)
{
    ifstream infile(dictionaryFile);
    // check if valid
    if (!infile)
    {
        return false;
    }
    string s;
    while (getline(infile, s))
    {
        bool add = true;
        
        //convert them all to lowercase
        for (int i = 0; i < s.size(); i++) {
            if (!isalpha(s[i]) && s[i] != APOSTROPHE)
            {
                add = false; //if not an allowed character
                break;
            }
            s[i] = tolower(s[i]);
        }
        if (add)
        {
//            dictSet.insert(s);
            Node* curr = m_trie->getRoot();
            for (int i = 0; i < s.length(); i++)
            {
                if (curr->children[s[i]  - 'a'] == nullptr) // 97 is ascii for a
                {
                    // create new node
                    curr->children[s[i]  - 'a'] = new Node(s[i]);
                }
                // go to next node
                curr = curr->children[s[i]  - 'a'];
            }
            curr->isWord = true;
        }
    }
    return true;
}

bool StudentSpellCheck::spellCheck(std::string word, int max_suggestions, std::vector<std::string>& suggestions) {
	return false; // TODO
    
    // make it to lower
}

void StudentSpellCheck::spellCheckLine(const std::string& line, std::vector<SpellCheck::Position>& problems) {
	// TODO
}

