//
//  StudentSpellCheck.hpp
//  Project4
//
//  Created by Buzz Fann on 3/3/21.
//

#ifndef STUDENTSPELLCHECK_H_
#define STUDENTSPELLCHECK_H_

#include "SpellCheck.h"

#include <string>
#include <vector>

class StudentSpellCheck : public SpellCheck {
public:
    StudentSpellCheck() { }
    virtual ~StudentSpellCheck();
    bool load(std::string dict_file);
    bool spellCheck(std::string word, int maxSuggestions, std::vector<std::string>& suggestions);
    void spellCheckLine(const std::string& line, std::vector<Position>& problems);

private:

};

#endif  // STUDENTSPELLCHECK_H_
