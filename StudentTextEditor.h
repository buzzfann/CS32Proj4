//
//  StudentTextEditor.hpp
//  Project4
//
//  Created by Buzz Fann on 3/3/21.
//

#ifndef STUDENTTEXTEDITOR_H_
#define STUDENTTEXTEDITOR_H_

#include "TextEditor.h"

class Undo;

class StudentTextEditor : public TextEditor {
public:

    StudentTextEditor(Undo* undo);
    ~StudentTextEditor();
    bool load(std::string file);
    bool save(std::string file);
    void reset();
    void move(Dir dir);
    void del();
    void backspace();
    void insert(char ch);
    void enter();
    void getPos(int& row, int& col) const;
    void getLines(int startRow, int numRows, std::vector<std::string>& lines) const;
    void undo();

private:

};

#endif // STUDENTTEXTEDITOR_H_

