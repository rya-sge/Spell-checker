

#ifndef ASD2_LABS_2020_HASHMAPSEPARATECHAINING_H
#define ASD2_LABS_2020_HASHMAPSEPARATECHAINING_H


#include <cstdlib>
#include <vector>
#include <list>
#include <algorithm>
#include "HashMapWrapper.h"




template<typename T>
class HashMapSeparateChaining : public HashMapWrapper<T> {

    typedef std::list<T> Bucket;
    typedef std::vector<Bucket> HashMap;

private:
    HashMap* hashMap;
    const size_t MIN_VALUE_M = 2;
    // Valeurs par défaut
    size_t M = MIN_VALUE_M;
    size_t N = 0;

    const double MAX_FACTOR = 8;
    const double MIN_FACTOR = 2;

    const size_t DIV_FACTOR_COEF = 2;
    const size_t MUL_FACTOR_COEF = 2;

    /**
     * @brief donne le hash de la clé modulo m.
     * @param key la clé.
     * @param m modulo.
     * @return le hash de la clé modulo m.
     */
    size_t hash(T key, size_t m) const{
        return std::hash<T>()(key) % m;
    }

    /**
     * @brief Change le nombre de buckets et fais le hash de toutes les clés
     *        afin de les réinsérer au bon endroit.
     * @param newM le nouveau nombre de buckets.
     */
    void realloc(size_t newM){
        size_t hashCalcul;
        HashMap* hashMapNew = new HashMap(newM);
        for (size_t i = 0; i < M; ++i)  {
            for (auto j = hashMap->at(i).begin(); j != hashMap->at(i).end(); ++j) {
                T k = *j;
                hashCalcul = hash(k, newM);
                hashMapNew->at(hashCalcul).push_front(k);
            }
        }
        delete hashMap;
        hashMap = hashMapNew;
        M = newM;
    }

public:

    /**
     * Constructeur
     */
    HashMapSeparateChaining(){
        hashMap = new HashMap(2);
    }

    /**
     * Destructeur
     */
    ~HashMapSeparateChaining() {
        delete hashMap;
        hashMap = NULL;
    }

    /**
     * @bief Insère une clé dans la hash map.
     * @param key la clé à insérer.
     */
    void insert(const T &key) {

        if(contains(key))
            return;

        N++;
        size_t occupancy = N / M;

        if (occupancy >= MAX_FACTOR) {
            size_t Mnew = M * DIV_FACTOR_COEF;
            realloc(Mnew);
        }

        size_t hKey = std::hash<T>()(key) % M;

        hashMap->at(hKey).push_front(key);
    }

    /**
     * Permet de savoir si un clé est dans la hash map.
     * @param key la clé cherchée.
     * @return vrai si la clé est contenue, sinon faux.
     */
    bool contains(const T& key) const {
        size_t index = hash(key, M);

        return (find(hashMap->at(index).begin(), hashMap->at(index).end(), key) != hashMap->at(index).end());
    }

    /**
     * @brief Supprime une clé.
     * @param key la clé à supprimer.
     * @return vrai s'il y a bien eu une supression. Faux si ce n'est pas le cas.
     */
    bool erase(const T& key) {
        size_t index = hash(key, M);
        //peut-être utiliser contains:
        auto it = std::find(hashMap->at(index).begin(), hashMap->at(index).end(), key);
        if(it != hashMap->at(index).end()){
            hashMap->at(index).erase(it);
            --N;
            if(N / M <= MIN_FACTOR && M > MIN_VALUE_M){
                realloc(M / MUL_FACTOR_COEF );
            }
        }else{
            return false;
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
     * @brief donne le coeficient de multiplication.
     * @return le coeficient de multiplication.
     */
    size_t getMulCoefFactor() const {
        return MUL_FACTOR_COEF;
    }

     /**
      * @brief donne le coeficient de division.
      * @return le coeficient de division.
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

#endif //ASD2_LABS_2020_HASHMAPSEPARATECHAINING_H
