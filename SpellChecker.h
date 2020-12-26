//
// Created by david on 23.12.20.
//

#include <vector>
#include "Dictionary.h"
#include "Suggestions.h"

#ifndef ASD2_LABS_2020_SPELLCHECKER_H

template <typename dicoType>
class SpellChecker {

    const Dictionary<dicoType>* dictionary;
    std::vector<Suggestions<dicoType>> typos;

private:

    std::string sanitizeWord(const std::string& w) const {

        std::string saneWord;
        for(char c : w){
            if(!isalpha(c) && c != '\'')
                continue; // skip non alpha and apostrophe
            else if(isupper(c))
                c = (char)tolower(c); // remove uppercase

            saneWord += c;

        }

        // loop needed in the case there are multiple apostrophes at the beginning/end character
        // i.e "'''''test'''''"
        bool apoFound = true;
        while(apoFound){
            if(saneWord.back() == '\'')
                saneWord.pop_back();
            else if(saneWord.front() == '\'')
                saneWord = saneWord.substr(1, saneWord.size() - 1);
            else
                apoFound = false;
        }

        return saneWord;

    }

    void checkWordSpelling(const std::string& word){
        if(word.length() && !dictionary->contains(word)) {
            Suggestions<dicoType> suggestions(word, *dictionary);
            typos.push_back(suggestions);
        }
    }

public:

    SpellChecker(const std::string& filename, const Dictionary<dicoType>& dico) : dictionary(&dico){
        std::string line;
        std::ifstream file;

        file.open(filename);

        if(!file.is_open()){
            std::cout << '\n' << "Erreur de lecture du fichier";
            return;
        }

        while(!file.eof()){
            std::getline(file, line);
            std::istringstream iss(line);
            std::string token;

            while(getline(iss, token, ' ')){
                // add every word
                std::string word = sanitizeWord(token);
                checkWordSpelling(word);
            }
        }

        file.close();

    }

    bool writeOutput(const std::string& filename) const{
        std::ofstream file;
        file.open(filename);

        if(!file.is_open()){
            std::cout << '\n' << "Erreur de lecture du fichier";
            return false;
        }

        file << result();

        file.close();
    }

    std::string result() const {
        std::string output;
        for(const Suggestions<dicoType>& v : typos){
            output += "*" + v.getAOP() + "\n";
            for(int i = 1; i <= 4; ++i){
                std::vector<std::string> suggestions;
                switch(i) {
                    case 1: suggestions = v.getTooManyChar(); break;
                    case 2: suggestions = v.getTooFewChar() ; break;
                    case 3: suggestions = v.getWrongChar()  ; break;
                    case 4: suggestions = v.getSwapedChar() ; break;
                    default: break;
                }

                for(const std::string& s : suggestions){
                    output += " ";
                    output += char(i + '0');
                    output += ":" + s + "\n";
                }
            }
        }

        return output;

    }

};



#define ASD2_LABS_2020_SPELLCHECKER_H

#endif //ASD2_LABS_2020_SPELLCHECKER_H
