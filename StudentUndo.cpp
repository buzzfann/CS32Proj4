#include "StudentUndo.h"

Undo* createUndo()
{
	return new StudentUndo;
}

void StudentUndo::submit(const Action action, int row, int col, char ch) {
	// TODO
    // switch statement for each action
    undoObj un;
    switch(action)
    {
            // if insert
        case INSERT:
             un = {INSERT, row, col, ch};
            undoStack.push(un);
            break;
        case DELETE:
             un = {DELETE, row, col, ch};
            undoStack.push(un);
            break;
        case JOIN:
             un = {JOIN, row, col, ch};
            undoStack.push(un);
            break;
        case SPLIT:
             un = {SPLIT, row, col, ch};
            undoStack.push(un);
            break;
        case ERROR:
            break;
    }
}

StudentUndo::Action StudentUndo::get(int& row, int& col, int& count, std::string& text) {
    
    return Action::ERROR;  // TODO
}

void StudentUndo::clear() {
	// TODO
    // while not empty, pop off the undo objects
    while (!undoStack.empty())
    {
        undoStack.pop();
    }
}
