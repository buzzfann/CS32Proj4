//
//  StudentTextEditor.cpp
//  Project4
//
//  Created by Buzz Fann on 3/3/21.
//

#include "StudentTextEditor.h"
#include "Undo.h"
#include <string>
#include <vector>

TextEditor* createTextEditor(Undo* un)
{
    return new StudentTextEditor(un);
}

StudentTextEditor::StudentTextEditor(Undo* undo)
 : TextEditor(undo) {
    // TODO
}

StudentTextEditor::~StudentTextEditor()
{
    // TODO
}

bool StudentTextEditor::load(std::string file) {
    return false;  // TODO
}

bool StudentTextEditor::save(std::string file) {
    return false;  // TODO
}

void StudentTextEditor::reset() {
    // TODO
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
}

void StudentTextEditor::getLines(int startRow, int numRows, std::vector<std::string>& lines) const {
    // TODO
}

void StudentTextEditor::undo() {
    // TODO
}

