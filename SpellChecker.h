//
// Created by david on 23.12.20.
//

#include <vector>
#include "Dictionary.h"
#include "Suggestions.h"
#include "Utils/sanitizeWord.h"

#ifndef ASD2_LABS_2020_SPELLCHECKER_H

template <typename dicoType>
class SpellChecker {

    const Dictionary<dicoType>* dictionary;
    std::vector<Suggestions<dicoType>> typos;

private:

    /**
     * @brief Check if the word is valid, and if it isn't, saves the typo with its suggestions
     * @param word
     */
    void checkWordSpelling(const std::string& word){

        if(word.length() && !dictionary->contains(word)) {
            // Generate suggestions
            Suggestions<dicoType> suggestions(word, *dictionary);
            typos.push_back(suggestions);
        }
    }

public:

    /**
     * @param filename
     * @param dico
     */
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

            // check every word in the file
            while(getline(iss, token, ' ')){
                std::string word = sanitizeWord(token);
                checkWordSpelling(word);
            }
        }

        file.close();

    }

    /**
     * Outputs the result in the file given in parameter
     * @param filename
     * @return true if the file has been written successfully
     */
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

    /**
     * Returns the result of the spell checking in a string
     * @return every typo with their suggestions
     */
    std::string result() const {
        std::string output;

        for(const Suggestions<dicoType>& v : typos){

            output += "*" + v.getBaseWord() + "\n";

            // 4 types of typos
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
