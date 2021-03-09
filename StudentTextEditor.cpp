#include "StudentTextEditor.h"
#include "Undo.h"
#include <string>
#include <vector>
#include <list>
#include <map>
#include <fstream>
#include <iostream>

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
//    list<string>::iterator getRow = textList.begin();
//    // move the iterator to position y of the
//    for (int i = 0; i < m_row; i++)
//    {
//        getRow++;
//    }
//    string temp = *getRow;
    std::list<std::string>::iterator tempIt = it;
	// TODO
    switch (dir) {
        case Dir::UP:
            if (m_row != 0)
            {
                m_row--;
                it--;
            }
            // check if empty line
            if ((*it).length() < m_col)
            {
                m_col = (*it).length() - 1;
            }
            break;
        case DOWN:
            if (tempIt++ != textList.end())
            {
                it++;
                m_row++;
            }
            // check if empty line
            if ((*it).length() < m_col)
            {
                m_col = (*it).length() - 1;
            }
            break;
        case Dir::LEFT:
            if (m_col > 0)
            {
                m_col--;
            }
            else
            {
                it--;
                m_col = (*it).length() - 1;
                m_row--;
            }
            break;
        case Dir::RIGHT:
            if (m_col < (*it).length() - 1)
            {
                m_col++;
            }
            else
            {
                it++;
                m_col = (*it).length() - 1;
                m_row++;
            }
            break;
        case Dir::HOME:
            break;
        case Dir::END:
            break;

        default:
            break;
    }
}

void StudentTextEditor::del() {
	// TODO
    // two cases --> first check to see if at m_col is at the last position in the list
    // it's there, then need to merge that list with next list member
    // erase a member
    // other case
    // just delete a character using substring
    // m_col remains the same
    if (m_col == (*it).length() - 1)
    {
        // merge with the next line
        std::list<std::string>::iterator next = it;
        next++;
        string nextLine = *next;
        textList.erase(next);
        *it = *it + nextLine;
    }
    string temp = *it;
    string temp2 = temp.substr(m_col+1);
    temp = temp.substr(0, m_col) + temp2;
    *it = temp;
}

void StudentTextEditor::backspace() {
	// TODO
    // two cases --> first check to see if at m_col is at the first position in the list
    // it's there, then need to merge that list and previous member
    // other case
    // just delete a character using substring
    // m_col moves
    if (m_col == 0)
    {
        //merge list with previous list
        std::list<std::string>::iterator curr = it;
        it--;
        string prevLine = *it;
        // this captures the line minus the last character (which will be deleted)
        prevLine = prevLine.substr(0, prevLine.length()-1);
        std::cout << prevLine << std::endl;
        *it = prevLine;
        if ((*it).length() != 0)
        {
            m_col = (*it).length() - 1;
        }
        // combine it with next line
        *it = *it + *curr;
        textList.erase(curr);
        m_row--;
    }
    else
    {
        string temp = *it;
        string temp2 = temp.substr(m_col);
        temp = temp.substr(0, m_col-1) + temp2;
        *it = temp;
        m_col--;
    }
}

void StudentTextEditor::insert(char ch) {
	// TODO
    // check if ch is valid
    if (ch > 0)
    {
        // now check if there's a tab
        if (ch == '\t')
        {
            (*it).insert(m_col, 4, ' ');
            m_col += 4;
        }
        string temp = *it;
        string temp2 = temp.substr(m_col);
        temp = temp.substr(0, m_col) + ch + temp2;
        *it = temp;
        m_col++;
    }

}

void StudentTextEditor::enter() {
	// TODO
    // substring current position-end, then cut that out, then create new member and make *it the substring
    list<string>::iterator getRow = it;
    getRow++;
    //split up the line
    string temp = *it;
    string temp0 = temp.substr(0, m_col);
    *it = temp0;
    temp = temp.substr(m_col);
    
    textList.emplace(getRow, temp);
    it++;
    // increment the row, set m_col to zero
    m_row++;
    m_col = 0;
}

void StudentTextEditor::getPos(int& row, int& col) const {
	// TODO
    row = m_row;
    col = m_col;
}

int StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const
{
//    // if invalid rows
//    if (startRow < 0 || numRows < 0 || startRow >= lines.size())
//    {
//        return -1;
//    }
//    // if starting row is the last line of lines
//    if (startRow == lines.size() - 1)
//    {
//        lines.clear();
//        return 0;
//    }
//    // create temp vector container
//    std::vector<std::string> temp;
//    std::vector<std::string>::const_iterator start = lines.cbegin() + startRow;
////    std::vector<std::string>::const_iterator temporary = start;
//    int i = 0;
//    // iterate through, decreasing numRows and make sure start isn't at the end
//    for (; numRows > 0 && start != lines.cend(); start++, numRows--, i++)
//    {
//        std::string s = *start;
////        start = lines.erase(start);
//        temp.push_back(s);
//    }
//    lines.clear();
//    lines = temp;
//    return i;
    if (startRow < 0 || numRows < 0 || startRow >= textList.size())
    {
        return -1;
    }
    if (startRow == textList.size() - 1)
    {
        lines.clear();
        return 0;
    }
    lines.clear();
    std::list<std::string>::const_iterator start = it;
    advance(start, startRow-m_row);
    int n = 0;
    for (int i = 0; i < numRows; i++)
    {
        if (start != textList.end())
        {
            lines.push_back(*start);
            n++;
            start++;
        }
    }
    return n;
}

void StudentTextEditor::undo() {
	// TODO
}
