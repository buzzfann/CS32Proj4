#ifndef STUDENTUNDO_H_
#define STUDENTUNDO_H_

#include "Undo.h"
#include <stack>
#include <string>

class StudentUndo : public Undo {
public:

	void submit(Action action, int row, int col, char ch = 0);
	Action get(int& row, int& col, int& count, std::string& text);
	void clear();

private:
    bool batchIns = false;
    bool batchSplit = false;
    bool batchDel = false;
    // define undoObj struct
    struct undoObj
    {
    public:
        undoObj(Action action, int row, int col, int count, std::string lastEdited)
        {
            this->action = action;
            e_row = row;
            e_col = col;
            this->count = count;
            this->lastEdited = lastEdited;
        }
        Action action;
        int e_row;
        int e_col;
        int count;
        std::string lastEdited;
    };
    void setFalse(bool one, bool two) {one = false; two = false;}
    std::stack<undoObj*> undoStack;

};

#endif // STUDENTUNDO_H_

/*
 multiple of the same action followed by a movement and THEN another action count as two
 distinct actions.
 
 have a batch boolean?
    whenever you do an action, set batch to true and push
    when batch is true and you repeat an action at the correct location
    record the top of the stack, pop it, combine it with the current action,
    and push it back onto the stack
 
 switch statement for each action to determine next "good" position
 */
