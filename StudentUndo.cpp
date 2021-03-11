#include "StudentUndo.h"
#include <iostream>

Undo* createUndo()
{
    return new StudentUndo;
}

void StudentUndo::submit(const Action action, int row, int col, char ch) {
	// TODO
    // switch statement for each action
    std::string last(ch, 1);
    undoObj* un = new undoObj(Action::ERROR, row, col, 1, last);
    
    switch(action)
    {
            // if insert
        case Undo::Action::INSERT:
            setFalse(batchDel, batchSplit);
            // if batch is true
            if (!undoStack.empty() && batchIns == true && undoStack.top()->e_col == col - undoStack.top()->count && undoStack.top()->e_row == row)
            {
                // unallocate the memory
                delete un;
                un = undoStack.top();
                un->count = un->count + 1;
                un->lastEdited = un->lastEdited + ch; // then add on the char to it
            }
            else // batch is false
            {
                un->action = INSERT;
                un->e_row = row;
                un->e_col = col;
                un->lastEdited = ch;
                undoStack.push(un);
                batchIns = true;
            }
            break;
        case Undo::Action::DELETE:
            setFalse(batchIns, batchSplit);
            
            if (!undoStack.empty() && undoStack.top()->e_col == col + un->count && batchDel && undoStack.top()->e_row == row) // backspace
            {
                delete un;
                un = undoStack.top();
                un->lastEdited = ch + un->lastEdited;
                un->e_col = col;
                un->count += 1;
            }
            else if (!undoStack.empty()&& undoStack.top()->e_col == col && batchDel && undoStack.top()->e_row == row) // delete
            {
                delete un;
                un = undoStack.top();
                un->lastEdited = un->lastEdited + ch;
//                un->e_col = col;
                un->count += 1;
            }
            else
            {
                un->action = DELETE;
                un->e_row = row;
                un->e_col = col;
                un->lastEdited = ch;
                undoStack.push(un);
                batchDel = true;
            }
            break;
        case Undo::Action::JOIN:
            setFalse(batchDel, batchIns);
            batchSplit = false;

            un->action = JOIN;
            un->e_row = row;
            un->e_col = col;
            un->lastEdited = ch;
            undoStack.push(un);
            break;
        case Undo::Action::SPLIT:
            setFalse(batchDel, batchIns);
            un->action = SPLIT;
            un->e_row = row;
            un->e_col = col;
            un->lastEdited = ch;
            undoStack.push(un);
            break;
        case ERROR:
            break;
    }
}

StudentUndo::Action StudentUndo::get(int& row, int& col, int& count, std::string& text) {
    Action retAction;
    if (undoStack.empty())
    {
        return Undo::Action::ERROR;
    }
    undoObj* topUndo = undoStack.top();
    Action topAction = topUndo->action;
    switch (topAction)
    {
        case Undo::INSERT:
            retAction = Undo::DELETE;
            // starting location
            row = topUndo->e_row;
            col = topUndo->e_col + topUndo->count - 1;
            count = topUndo->count;

            break;
        case Undo::DELETE:
            retAction = Undo::INSERT;
            // starting location
            row = topUndo->e_row;
            col = topUndo->e_col;
            text = topUndo->lastEdited;

            count = topUndo->count;
            break;
        case Undo::SPLIT:
            retAction = Undo::JOIN;
            row = topUndo->e_row;
            col = topUndo->e_col;

            count = 1;
            break;
        case Undo::JOIN:
            retAction = Undo::SPLIT;
            // delete at end of line
            if (topUndo->lastEdited == "")
            {
                // do nothing
            }
            else if (topUndo->lastEdited == "\n")    //backspace at front of line
            {
                // do nothing?
            }
            count = 1;

            row = topUndo->e_row;
            col = topUndo->e_col;

            break;
        case Undo::Action::ERROR:
            retAction = Undo::Action::ERROR;
            break;
    }
    undoStack.pop();

    return retAction;  // TODO

}

void StudentUndo::clear() {
	// TODO
    // while not empty, pop off the undo objects
    while (!undoStack.empty())
    {
        delete undoStack.top();
        undoStack.pop();
    }
}
