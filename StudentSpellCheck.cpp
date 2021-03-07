//
//  StudentSpellCheck.cpp
//  Project4
//
//  Created by Buzz Fann on 3/3/21.
//

#include "StudentSpellCheck.h"
#include <string>
#include <vector>

SpellCheck* createSpellCheck()
{
    return new StudentSpellCheck;
}

StudentSpellCheck::~StudentSpellCheck() {
    // TODO
}

bool StudentSpellCheck::load(std::string dictionaryFile) {
    return false; // TODO
}

bool StudentSpellCheck::spellCheck(std::string word, int max_suggestions, std::vector<std::string>& suggestions) {
    return false; // TODO
}

void StudentSpellCheck::spellCheckLine(const std::string& line, std::vector<SpellCheck::Position>& problems) {
    // TODO
}
