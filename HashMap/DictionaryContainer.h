/* ---------------------------
Laboratoire : 8 - Correcteur orthographique
Fichier : DictionaryContainer.h
Auteurs : David Pellissier, Michael Ruckstuhl, Ryan Sauge
Date : 23.01.2021

But : Wrapper servant à définir les fonctions contains, insert et erase dans le but de pouvoir utiliser n'importe
        quelle structure dans un dictionnaire

Compilateur : gcc 9.3.0
--------------------------- */

#ifndef ASD2_LABS_2020_DICTIONARYCONTAINER_H
#define ASD2_LABS_2020_DICTIONARYCONTAINER_H

#include <functional>


template<typename T>
class DictionaryContainer {

    using boolFunction =  std::function<bool(const T &key)>;
    using voidFunction =  std::function<void(const T &key)>;

    const boolFunction containsF;
    const voidFunction insertF;
    const voidFunction eraseF;

public:

    /**
     * @param containsFunction Fonction retournant vrai si la clé passée en paramètre existe une structure
     * @param insertFunction  Fonction insérant une clé dans une structure
     * @param eraseFunction  Fonction supprimant une clé dans une structure
     * @details La structure n'est pas stockée dans cette classe.
     *          Elle doit pouvoir être accédée à l'intérieur de la fonction lambda
     */
    DictionaryContainer(const boolFunction &containsFunction, const voidFunction &insertFunction,
                        const voidFunction &eraseFunction)
            : containsF(containsFunction), insertF(insertFunction), eraseF(eraseFunction) {}

    /**
     * @brief Appelle la fonction de recherche de clé
     * @param key clé à vérifier
     * @return true si la clé existe
     */
    bool contains(const T &key) const {
        return containsF(key);
    }

    /**
     * @brief Appelle la fonction d'insertion avec la clé donnée
     * @param key
     */
    void insert(const T &key) const {
        insertF(key);
    }

    /**
     * @brief Appelle la fonction de suppression de clé
     * @param key
     */
    void erase(const T &key) const {
        eraseF(key);
    }
};

#endif //ASD2_LABS_2020_DICTIONARYCONTAINER_H
