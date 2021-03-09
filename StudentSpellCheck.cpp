#include "StudentSpellCheck.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

///Users/buzzfann/Downloads/Wurd/Wurd/warandpeace.txt

const int APOSTROPHE = '\'';
SpellCheck* createSpellCheck()
{
	return new StudentSpellCheck;
}

void StudentSpellCheck::deleteNodes(Node* root)
{
    // destructor
    if (root == nullptr)
    {
        return;
    }
    for (int i = 0; i < 27; i++)
    {
        deleteNodes(root->children[i]);
    }
    delete root;
}

StudentSpellCheck::~StudentSpellCheck() {
	// TODO
    deleteNodes(m_trie->getRoot());
    delete m_trie;
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
    m_trie = new Trie();
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
            Node* curr = m_trie->getRoot();
            for (int i = 0; i < s.length(); i++)
            {
                // if apostrophe
                if (s[i] == APOSTROPHE)
                {
                    if (curr->children[26] == nullptr)
                    {
                        curr->children[26] = new Node(s[i]);
                    }
                    curr = curr->children[26];
                }
                else
                {
                    if (curr->children[s[i]  - 'a'] == nullptr)
                    {
                        // create new node
                        curr->children[s[i]  - 'a'] = new Node(s[i]);
                    }
                    // go to next node
                    curr = curr->children[s[i]  - 'a'];
                }
            }
            curr->isWord = true;
        }
    }
    return true;
}

bool StudentSpellCheck::search(std::string word, Node* root)
{
    bool isIn = false;
    for (int i = 0; i < word.length(); i++)
    {
        if (!isalpha(word[i]) && word[i] != APOSTROPHE)
        {
            return false;
        }
        if (word[i] == APOSTROPHE)
        {
            if (root->children[26] != nullptr)
            {
                root = root->children[26];
//                // if at the end of the correct word
                if (root->isWord == true && i == word.length()-1)
                {
                    isIn = true;
                }
                continue;
            }
        }
        else
        {
            // check if the letter is present as a child
            if (root->children[word[i] - 'a'] != nullptr)
            {
                root = root->children[word[i] - 'a'];
    //            // if at the end of the correct word
                if (root->isWord == true && i == word.length()-1)
                {
                    isIn = true;
                }
                continue;
            }
        }
        break;
    }
//    root = root->children[0];
//    cout << root->c << endl;
//    root = root->children[0];
//    cout << root->c << endl;
//    root = root->children['h' - 'a'];
//    cout << root->c << endl;
//    root = root->children['s' - 'a'];
//    cout << root->c << endl;
//    bool isWord = root->isWord;
//    cout << isWord << endl;
    
    
//    bool isIn = true;
//    int i = 0;
//        while (root->isWord == false && i < word.length())
//        {
//            // check if the letter is present as a child
//            if (root->children[word[i] - 'a'] != nullptr)
//            {
//                // does this break out of current iteration of the for loop?
//                // or the entire loop itself? should i use continue?
//                i++;
//                root = root->children[word[i] - 'a'];
//                continue;
//            }
//            // if it's null but you're not at the end of the word
//            else if (root->children[word[i] - 'a'] == nullptr)
//            {
//                isIn = false;
//                break;
//            }
//        }
    return isIn;
}

bool StudentSpellCheck::spellCheck(std::string word, int max_suggestions, std::vector<std::string>& suggestions)
{
    bool isIn = false;
    // make it lowercase
    for (int i = 0; i < word.length(); i++)
    {
        word[i] = tolower(word[i]);
    }
    // check if it's in the trie
    Node* root = m_trie->getRoot();
    // search for the word
    isIn = search(word, root);

    // if it's not in the trie then spellcheck it
    if (isIn == false)
    {
        suggestions.clear();
        for (int i = 0; i < word.length(); i++)
        {
            char letter = 'a';
            for (int j = 0; j < ALPHABET_SIZE_APOS; j++)
            {
                root = m_trie->getRoot();
                bool isProposed = false;
                letter = 'a' + j;
                string proposedWord = "";
                if (i < word.length() - 1)
                {
                    proposedWord = word.substr(0, i) + letter + word.substr(i+1);
                }
                else
                {
                    proposedWord = word.substr(0, i) + letter;
                }
                isProposed = search(proposedWord, root);
                // this will run maxsuggestions times in worst case
                if (isProposed && suggestions.size() < max_suggestions)
                {
                    suggestions.push_back(proposedWord);
                }
            }
        }
    }
    return isIn;
}

void StudentSpellCheck::spellCheckLine(const std::string& line, std::vector<SpellCheck::Position>& problems)
{
	// TODO
    // clear problems
    problems.clear();
    int start = 0;
    // iterate through line
    string temp = "";
    string lineTemp = line; // this will end up being a lowercase version of the line
    for (int i = 0; i < line.length(); i++)
    {
        Node* root = m_trie->getRoot();
        lineTemp[i] = tolower(lineTemp[i]);
        // while a letter or apostrophe, increment i
        while ((isalpha(line[i]) || line[i] == '\'') && i < line.length())
        {
            i++;
            lineTemp[i] = tolower(lineTemp[i]);
        }
        string temp = lineTemp;
        temp = temp.substr(start, i-start);
        // search
        bool spelled = false;
        spelled = search(temp, root);
        if (!spelled)
        {
            // put into problems vector
            Position pos;
            pos.start = start;
            pos.end = i-1;
            problems.push_back(pos);
        }
        // while i isn't a letter or apostrophe, increment i
        while (!isalpha(line[i]) && line[i] != '\'' && i < line.length())
        {
            i++;
        }
        start = i;
        lineTemp[i] = tolower(lineTemp[i]);
    }
}
    


