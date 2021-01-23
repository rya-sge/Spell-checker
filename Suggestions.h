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

    /**
     * @param basew Mot à corriger
     * @param dictionary
     */
    Suggestions(const std::string& basew, const Dictionary<DicoType>& dictionary) : baseWord(basew), dictionary(&dictionary){
        tooMany();
        tooFew();
        wrong();
        swap();
    }

    /**
     * @brief Retourne les suggestions de caractère en trop
     * @return tooManyChar
     */
    const std::vector<std::string> &getTooManyChar() const {
        return tooManyChar;
    }

    /**
     * @brief Retourne les suggestions de caractère manquant
     * @return tooFewChar
     */
    const std::vector<std::string> &getTooFewChar() const {
        return tooFewChar;
    }

    /**
     * @brief Retourne les suggestions de lettre incorrecte
     * @return wrongChar
     */
    const std::vector<std::string> &getWrongChar() const {
        return wrongChar;
    }

    /**
     * @brief Retourne les suggestions de lettres échangées
     * @return swappedChar
     */
    const std::vector<std::string> &getSwapedChar() const {
        return swappedChar;
    }

    /**
     * @brief Retourne le mot de base
     * @return baseWord
     */
    const std::string &getBaseWord() const {
        return baseWord;
    }

private:

    /**
     * @brief Vérifie chaque possibilité de nouveau mot en supprimant une lettre du mot de base
     */
    void tooMany() {
        std::string var;
        for (size_t i = 0; i < baseWord.length(); ++i) {
            var = baseWord;
            var.erase(i, 1);
            if(dictionary->contains(var))
                tooManyChar.push_back(var);
        }
    }

    /**
     * @brief Vérifie chaque possibilité de nouveau mot en ajoutant une lettre au mot de base
     */
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

    /**
     * @brief Vérifie chaque possibilité de nouveau mot en changeant une lettre du mot de base
     */
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

    /**
     * @brief Vérifie chaque possbilité de nouveau mot en échangeant deux lettres du mot de base
     */
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

