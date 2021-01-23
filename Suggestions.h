//
// Created by micha on 2020-12-23.
//

#ifndef ASD2_LABS_2020_SUGGESTIONS_H
#define ASD2_LABS_2020_SUGGESTIONS_H

#include <vector>
#include <string>
#include <iostream>
#include "Dictionary.h"


template <typename DicoType>
class Suggestions {
private:
    std::string baseWord;
    std::vector<std::string> tooManyChar;
    std::vector<std::string> tooFewChar;
    std::vector<std::string> wrongChar;
    std::vector<std::string> swappedChar;

    const Dictionary<DicoType>* dictionary;
public:
    Suggestions(const std::string& aop, const Dictionary<DicoType>& dictionary) : baseWord(aop), dictionary(&dictionary){

        tooMany();
        tooFew();
        wrong();
        swap();
    }

    const std::vector<std::string> &getTooManyChar() const {
        return tooManyChar;
    }

    const std::vector<std::string> &getTooFewChar() const {
        return tooFewChar;
    }

    const std::vector<std::string> &getWrongChar() const {
        return wrongChar;
    }

    const std::vector<std::string> &getSwapedChar() const {
        return swappedChar;
    }

    const std::string &getBaseWord() const {
        return baseWord;
    }

private:
    void tooMany() {
        std::string var;
        for (size_t i = 0; i < baseWord.length(); ++i) {
            var = baseWord;
            var.erase(i, 1);
            if(dictionary->contains(var))
                tooManyChar.push_back(var);
        }
    }

    void tooFew() {
        std::string var;
        for (size_t i = 0; i <= baseWord.length(); ++i) {
            for (int j = 0; j < 26; ++j) {
                var = baseWord;
                var.insert(i, 1, char('a' + j));
                if(dictionary->contains(var))
                    tooFewChar.push_back(var);
            }
        }
    }

    void wrong() {
        std::string var;
        for (size_t i = 0; i < baseWord.length(); ++i) {
            for (int j = 0; j < 26; ++j) {
                var = baseWord;
                var.replace(i, 1, 1, char('a' + j));
                if(dictionary->contains(var))
                    wrongChar.push_back(var);
            }
        }
    }

    void swap() {
        std::string var;
        for (size_t i = 1; i < baseWord.length(); ++i) {
            var = baseWord;
            std::swap(var[i - 1], var[i]);
            if(dictionary->contains(var))
                swappedChar.push_back(var);
        }
    }

};

#endif //ASD2_LABS_2020_SUGGESTIONS_H

