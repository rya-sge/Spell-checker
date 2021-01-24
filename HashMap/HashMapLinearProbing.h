/* ---------------------------
Laboratoire : 8 - Correcteur orthographique
Fichier : HashMapLinearProbing.h
Auteurs : David Pellissier, Michael Ruckstuhl, Ryan Sauge
Date : 23.01.2021

But : Implémentation d'une table de hachage avec sondage linéaire

Compilateur : gcc 9.3.0
--------------------------- */

#ifndef ASD2_LABS_2020_HASHMAPLINEARPROBING_H
#define ASD2_LABS_2020_HASHMAPLINEARPROBING_H

#include <cstdlib>
#include <vector>
#include "HashMapWrapper.h"

template<typename T>
class HashMapLinearProbing : public HashMapWrapper<T> {


private:
    // Valeurs par défaut
    const size_t MIN_VALUE_M = 2;
    const double MAX_FACTOR = 1.0 / 2;
    const double MIN_FACTOR = 1.0 / 8;
    const size_t MUL_FACTOR_COEF = 2;
    const size_t DIV_FACTOR_COEF = 2;


    class HashNode {
    public:
        // V value;
        T key;

        /**
         * Utilisation des pointeurs pour différencier une case est vide(ptr == null)
         * d'une case contenant une clé
         * @param key
         */
        HashNode(T key) {
            // this->value = value;
            this->key = key;
        }
    };

    typedef std::vector<HashNode *> HashMap;

    size_t M = MIN_VALUE_M;
    size_t N = 0;

    HashMap *hashMap;

    /**
     * @brief donne le hash de la clé modulo m.
     * @param key la clé.
     * @param m modulo.
     * @return le hash de la clé modulo m.
     */
    size_t hash(const T &key, size_t m) const {
        return std::hash<T>()(key) % m;
    }

    /**
     *
     * @param hm hashmap où chercher la position
     * @param key
     * @param m
     * @param index
     */
    void findPosition(HashMap *hm, const T &key, size_t m, size_t &index) {
        while (hm->at(index) != NULL && hm->at(index)->key != key) {
            index = (index + 1) % m;
        }
    }

    /**
     * @brief Change le nombre de buckets et fait le hash de toutes les clés
     *        afin de les réinsérer au bon endroit.
     * @param newM le nouveau nombre de buckets.
     */
    void realloc(size_t newM) {
        HashMap *newHashMap = new HashMap(newM);

        for (HashNode *ptr: *hashMap) {
            if (ptr != NULL) {
                T key = ptr->key;
                // insert values into the new table
                size_t index = hash(key, newM);
                findPosition(newHashMap, key, newM, index);
                newHashMap->at(index) = ptr;
            }

        }

        HashMap *oldHashMap = hashMap;
        hashMap = newHashMap;
        delete oldHashMap;

        M = newM;
    }

public:

    /**
     * Constructeur
     */
    HashMapLinearProbing() {
        hashMap = new HashMap(M);
    }

    /**
     * Destructeur
     */
    ~HashMapLinearProbing() {
        for (HashNode *ptr : *hashMap) {

            delete ptr;
        }
        delete hashMap;
        hashMap = NULL;
    }

    /**
     * @brief Insère une clé dans la hash map.
     * @param key la clé à insérer.
     */
    void insert(const T &key) {
        // find first available index
        if (contains(key))
            return;

        size_t index = hash(key, M);
        findPosition(hashMap, key, M, index);
        hashMap->at(index) = new HashNode(key);
        ++N;

        if ((double) N / M >= MAX_FACTOR) {
            realloc(M * 2);
        }
    }

    /**
     * Permet de savoir si un clé est dans la hash map.
     * @param key la clé cherchée.
     * @return vrai si la clé est contenue, sinon faux.
     */
    bool contains(const T &key) const {
        size_t index = hash(key, M);
        size_t count = 0;

        while (count != N) {
            if (hashMap->at(index) != NULL && hashMap->at(index)->key == key)
                return true;
            else if (!hashMap->at(index))
                break;

            index = (index + 1) % M;
            ++count;
        }

        return false;
    }

    /**
     * @brief Supprime une clé.
     * @param key la clé à supprimer.
     * @return vrai s'il y a bien eu une suppression. Faux si ce n'est pas le cas.
     */
    bool erase(const T &key) {
        if (!contains(key)) return false;
        int i = hash(key, M);
        while (hashMap->at(i) == NULL || hashMap->at(i)->key != key) {
            i = (i + 1) % M;
        }
        delete hashMap->at(i); //Suppression objet pointé
        hashMap->at(i) = NULL;
        i = (i + 1) % M;
        while (hashMap->at(i) != NULL) {
            T keyToRedo = hashMap->at(i)->key;
            //Value valToRedo = vals[i];
            delete hashMap->at(i); //Suppression objet pointé
            hashMap->at(i) = NULL;
            // vals[i] = null;
            N--;
            insert(keyToRedo);
            i = (i + 1) % M;

        }
        --N;
        if (M > MIN_VALUE_M && (double) N / M <= MIN_FACTOR) {
            realloc(M / MUL_FACTOR_COEF);
        }
        return true;
    }

    /**
     * @brief donne le nombre d'éléments'.
     * @return le nombre d'éléments.
     */
    size_t size() const {
        return N;
    }

    /**
     * @brief donne le nombre de buckets.
     * @return le nombre de buckets.
     */
    size_t max_buckets() const {
        return M;
    }

    /**
     * @brief donne le facteur maximum.
     * @return le facteur maximum.
     */
    double getMaxFactor() const {
        return MAX_FACTOR;
    }

    /**
     * @brief donne le facteur minimum.
     * @return le facteur minimum.
     */
    double getMinFactor() const {
        return MIN_FACTOR;
    }

    /**
     * @brief donne le coefficient de multiplication.
     * @return le coefficient de multiplication.
     */
    size_t getMulCoefFactor() const {
        return MUL_FACTOR_COEF;
    }

    /**
     * @brief donne le coefficient de division.
     * @return le coefficient de division.
     */
    size_t getDivCoefFactor() const {
        return DIV_FACTOR_COEF;
    }

    /**
     * @brief renvoie le nombre de bucket minimum que peut avoir la hashmap.
     * @return le nombre de bucket minimum que peut avoir la hashmap.
     */
    size_t getMinValueForM() const {
        return MIN_VALUE_M;
    }
};


#endif //ASD2_LABS_2020_HASHMAPLINEARPROBING_H
