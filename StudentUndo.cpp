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
    // allocate memory for undoObj
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
            // check if backspace
            if (!undoStack.empty() && undoStack.top()->e_col == col + un->count && batchDel && undoStack.top()->e_row == row)
            {
                // unallocate memory
                delete un;
                un = undoStack.top();
                un->lastEdited = ch + un->lastEdited;
                un->e_col = col;
                un->count += 1;
            }
            // check if delete
            else if (!undoStack.empty()&& undoStack.top()->e_col == col && batchDel && undoStack.top()->e_row == row)
            {
                // unallocate memory
                delete un;
                un = undoStack.top();
                un->lastEdited = un->lastEdited + ch;
//                un->e_col = col;
                un->count += 1;
            }
            //otherwise
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
        // join
        case Undo::Action::JOIN:
            setFalse(batchDel, batchIns);
            batchSplit = false;
            // set variables
            un->action = JOIN;
            un->e_row = row;
            un->e_col = col;
            un->lastEdited = ch;
            undoStack.push(un);
            break;
        case Undo::Action::SPLIT:
            setFalse(batchDel, batchIns);
            // set variables
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
    // define the return action
    Action retAction;
    // return error if empty
    if (undoStack.empty())
    {
        return Undo::Action::ERROR;
    }
    // record the top of the stack
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
            if (topUndo->lastEdited == "")
            {
                // do nothing
            }
            else if (topUndo->lastEdited == "\n")    //backspace at front of line
            {
                // do nothing
            }
            count = 1;

            row = topUndo->e_row;
            col = topUndo->e_col;

            break;
        case Undo::Action::ERROR:
            retAction = Undo::Action::ERROR;
            break;
    }
    // pop off the stack
    undoStack.pop();

    return retAction;

}

void StudentUndo::clear() {
    // while not empty, pop off the undo objects
    while (!undoStack.empty())
    {
        delete undoStack.top();
        undoStack.pop();
    }
}
