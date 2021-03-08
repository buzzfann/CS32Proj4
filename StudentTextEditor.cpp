#include "StudentTextEditor.h"
#include "Undo.h"
#include <string>
#include <vector>
#include <list>
#include <map>
#include <fstream>

using namespace std;

TextEditor* createTextEditor(Undo* un)
{
	return new StudentTextEditor(un);
}

StudentTextEditor::StudentTextEditor(Undo* undo)
 : TextEditor(undo) {
	// TODO
     undObj = undo;
     m_row = 0;
     m_col = 0;
}

StudentTextEditor::~StudentTextEditor()
{
    // iterate through the list/map, deleting everything along the way
	// TODO
}

bool StudentTextEditor::load(std::string file) {
    ifstream infile(file);
    if (!infile)
    {
        return false;
    }
    reset();
    string s;
    while(getline(infile, s))
    {
        if (s[s.length() -1] == '\r')
        {
            s = s.substr(0, s.length()-1);
            s = s + '\n';
        }
        textList.push_back(s);
    }
    m_col = 0;
    m_row = 0;
    it = textList.begin();
//    string s;
//    std::list<std::string>::iterator it = textList.begin();
//    *it = "";
//    while (getline(infile, s))
//    {
//        for (int i = 0; i < s.size(); i++) {
//            if (s[i] == '\r')
//            {
//                break;
//            }
//            *it += s[i];
//        }
//        textList.push_back(*it);
//        it++;
//    }
    return true;  // TODO
}

bool StudentTextEditor::save(std::string file) {
    ofstream outfile(file);
    if ( ! outfile )           // Did the creation fail?
    {
        return false;
    }
    string s;
    std::list<std::string> temp = textList;
    while (!temp.empty())
    {
        outfile << temp.front() << "\n";
        temp.pop_front();
    }
    return true;
}

void StudentTextEditor::reset() {
	// TODO
    m_col = 0;
    m_row = 0;
    textList.clear();
}

void StudentTextEditor::move(Dir dir) {
	// TODO
//    switch (dir) {
//        case Dir::UP:
//            if (
//            break;
//        case DOWN:
//            break;
//        case Dir::LEFT:
//            break;
//        case Dir::RIGHT:
//            break;
//        case Dir::HOME:
//            break;
//        case Dir::END:
//            break;
//
//        default:
//            break;
//    }
}

void StudentTextEditor::del() {
	// TODO
    
}

void StudentTextEditor::backspace() {
	// TODO
}

void StudentTextEditor::insert(char ch) {
	// TODO
    list<string>::iterator getRow = textList.begin();
    // move the iterator to position y of the
    for (int i = 0; i < m_row; i++)
    {
        getRow++;
    }
//    *getY  --> this gives the string itself
    string temp = *getRow;
//    for (int i = 0; i < temp.length(); i++)
//    {
//        if (i == m_col)
//        {
//            char cTemp = temp[i];
//
//        }
//    }
    string temp2 = temp.substr(m_col);
    temp = temp.substr(0, m_col) + ch + temp2;
    *getRow = temp;
    
}

void StudentTextEditor::enter() {
	// TODO
    // substring current position-end, then cut that out, then create new member and make *it the substring
    list<string>::iterator getRow = textList.begin();
    // move the iterator to position row of the
    for (int i = 0; i < m_row; i++)
    {
        getRow++;
    }
    string temp = *getRow;
    string temp0 = temp.substr(0, m_col);
    *getRow = temp0;
    temp = temp.substr(m_col);
    getRow++;
    textList.insert(getRow, temp);
}

void StudentTextEditor::getPos(int& row, int& col) const {
	// TODO
    row = m_row;
    col = m_col;
}

int StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const
{
    // if invalid rows
    if (startRow < 0 || numRows < 0 || startRow >= lines.size())
    {
        return -1;
    }
    // if starting row is the last line of lines
    if (startRow == lines.size() - 1)
    {
        lines.clear();
        return 0;
    }
    // create temp vector container
    std::vector<std::string> temp;
    std::vector<std::string>::const_iterator start = lines.cbegin() + startRow;
//    std::vector<std::string>::const_iterator temporary = start;
    int i = 0;
    // iterate through, decreasing numRows and make sure start isn't at the end
    for (; numRows > 0 && start != lines.cend(); start++, numRows--, i++)
    {
        std::string s = *start;
//        start = lines.erase(start);
        temp.push_back(s);
    }
    lines.clear();
    lines = temp;
    return i;
}

void StudentTextEditor::undo() {
	// TODO
}
