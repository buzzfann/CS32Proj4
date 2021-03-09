#ifndef STUDENTUNDO_H_
#define STUDENTUNDO_H_

#include "Undo.h"

class StudentUndo : public Undo {
public:

	void submit(Action action, int row, int col, char ch = 0);
	Action get(int& row, int& col, int& count, std::string& text);
	void clear();

private:
    bool batch;

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
