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
     textList.push_back("");
     it = textList.begin();
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
            tempIt = it;
            tempIt++;
            if (tempIt != textList.end())
            {
                it++;
                m_row++;
            }
            // check if empty line
            else if ((*it).length() < m_col && (*it).length() >=0)
            {
                m_col = (*it).length() - 1;
            }
            break;
        case Dir::LEFT:
            if (m_col > 0)
            {
                m_col--;
            }
            else if (m_col == 0 && it != textList.begin())
            {
                it--;
                if ((*it).length() != 0)
                {
                    m_col = (*it).length() - 1;
                }
                else
                {
                    m_col = 0;
                }
                m_row--;
            }
            // else it's the first position and nothing will happen
            break;
        case Dir::RIGHT:
            tempIt = it;
            tempIt++;
            if (m_col < (*it).length() - 1 && (*it).length() != 0)
            {
                m_col++;
            }
            else if (tempIt++ != textList.end())
            {
                it++;
                // move to first position
                m_col = 0;
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
    
    //implement undo
}

void StudentTextEditor::backspace() {
	// TODO
    // two cases --> first check to see if at m_col is at the first position in the list
    // it's there, then need to merge that list and previous member
    // other case
    // just delete a character using substring
    // m_col moves
    if (m_col == 0 && m_row != 0)
    {
        //merge list with previous list
        std::list<std::string>::iterator curr = it;
        it--;
        string prevLine = *it;
//        getUndo()->submit(Undo::Action::JOIN, m_row-1, prevLine.length(), ' ');
        // this captures the line minus the last character (which will be deleted)
        prevLine = prevLine.substr(0, prevLine.length() - 1);
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
    else if (m_row == 0 && m_col == 0)
    {
        return;
    }
    else
    {
//        getUndo()->submit(Undo::Action::DELETE, m_row, m_col-1, (*it).at(m_col-1);
        string temp = *it;
        string temp2 = temp.substr(m_col);
        temp = temp.substr(0, m_col-1) + temp2;
        *it = temp;
        m_col--;
    }
    //implement undo
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
    //implement undo

}

void StudentTextEditor::enter() {
	// TODO
    // substring current position-end, then cut that out, then create new member and make *it the substring
    list<string>::iterator getRow = it;
    getRow++;
    //split up the line
    // if it's not the last on the line
    if (m_col != (*it).length() - 1)
    {
        string temp = *it;
        string temp0 = temp.substr(0, m_col);
        *it = temp0;
        temp = temp.substr(m_col);
        
        textList.emplace(getRow, temp);
    }
    else
    {
        textList.emplace(getRow, " ");
    }

    it++;
    // increment the row, set m_col to zero
    m_row++;
    m_col = 0;
    //implement undo
    //undObj.submit(SPLIT, ...)
}

void StudentTextEditor::getPos(int& row, int& col) const {
	// TODO
    row = m_row;
    col = m_col;
}

int StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const
{
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
    // if
    int row = 0;
    int col = 0;
    int count = 0;
    string oldText;
    Undo::Action job;
    job = getUndo()->get(row, col, count, oldText);
    std::list<std::string>::iterator temp = textList.begin();
    // insert
    if (job == Undo::Action::INSERT)
    {
        // iterate to the row passed
        for (int i = 0; i < row; i++)
        {
            temp++;
        }
        temp->insert(col, oldText);
    }
    // delete
    else if (job == Undo::Action::DELETE)
    {
        // iterate to the row passed
        for (int i = 0; i < row; i++)
        {
            temp++;
        }
        if (col == 0)
        {
            temp->erase((*temp).begin());
        }
        else
        {
            temp->erase((*temp).begin() + col - 1);
        }
    }
    // join
    else if (job == Undo::Action::JOIN)
    {
        for (int i = 0; i < row; i++)
        {
            temp++;
        }
        //DO
    }
    // split
    else if (job == Undo::Action::SPLIT)
    {
        for (int i = 0; i < row; i++)
        {
            temp++;
        }
        //DO
    }
    // if it's error
    else
    {
        return;
    }
    
}
