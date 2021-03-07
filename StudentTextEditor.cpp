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
     posX = 0;
     posY = 0;
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
    string s;
    std::list<std::string>::iterator it = textList.begin();
    *it = "";
    while (getline(infile, s))
    {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '\r')
            {
                break;
            }
            *it += s[i];
        }
        textList.push_back(*it);
        it++;
    }
    return false;  // TODO
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
    posX = 0;
    posY = 0;
    textList.clear();
}

void StudentTextEditor::move(Dir dir) {
	// TODO
}

void StudentTextEditor::del() {
	// TODO
}

void StudentTextEditor::backspace() {
	// TODO
}

void StudentTextEditor::insert(char ch) {
	// TODO
}

void StudentTextEditor::enter() {
	// TODO
}

void StudentTextEditor::getPos(int& row, int& col) const {
	// TODO
    row = posX;
    col = posY;
}

int StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const
{
    if (startRow < 0 || numRows < 0 || startRow >= lines.size())
    {
        return -1;
    }
    if (startRow == lines.size() - 1)
    {
        lines.clear();
        return 0;
    }
    std::vector<std::string> temp;
    std::vector<std::string>::const_iterator start = lines.cbegin() + startRow;
//    std::vector<std::string>::const_iterator temporary = start;
    int i = 0;
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
