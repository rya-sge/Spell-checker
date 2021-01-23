/* ---------------------------
Laboratoire : 8 - Correcteur orthographique
Fichier : HashMapWrapper.h
Auteurs : David Pellissier, Michael Ruckstuhl, Ryan Sauge
Date : 23.01.2021
But : Wrapper englobant les HashMap.

Compilateur : gcc 9.3.0
--------------------------- */

#ifndef ASD2_LABS_2020_HASHMAPWRAPPER_H
#define ASD2_LABS_2020_HASHMAPWRAPPER_H


template<typename T>
class HashMapWrapper {

public:

    /**
     * @brief Insère une clé dans la hash map.
     * @param key la clé à insérer.
     */
    virtual void insert(const T& key) = 0;

    /**
     * Permet de savoir si un clé est dans la hash map.
     * @param key la clé cherchée.
     * @return vrai si la clé est contenue, sinon faux.
     */
    virtual bool contains(const T& key) const = 0;

    /**
     * @brief Supprime une clé.
     * @param key la clé à supprimer.
     * @return vrai s'il y a bien eu une supression. Faux si ce n'est pas le cas.
     */
    virtual bool erase(const T& key) = 0;

    /**
     * @brief donne le nombre d'éléments'.
     * @return le nombre d'éléments.
     */
    virtual size_t size() const = 0;

    /**
     * @brief donne le nombre de buckets.
     * @return le nombre de buckets.
     */
    virtual size_t max_buckets() const = 0;

    /**
     * @brief donne le facteur maximum.
     * @return le facteur maximum.
     */
    virtual double getMaxFactor() const = 0;

    /**
     * @brief donne le facteur minimum.
     * @return le facteur minimum.
     */
    virtual double getMinFactor() const = 0;

    /**
     * @brief donne le coeficient de multiplication.
     * @return le coeficient de multiplication.
     */
    virtual size_t getMulCoefFactor() const = 0;

    /**
     * @brief donne le coeficient de division.
     * @return le coeficient de division.
     */
    virtual size_t getDivCoefFactor() const = 0;

    /**
     * @brief renvoie le nombre de bucket minimum que peut avoir la hashmap.
     * @return le nombre de bucket minimum que peut avoir la hashmap.
     */
    virtual size_t getMinValueForM() const = 0;
};



#endif //ASD2_LABS_2020_HASHMAPWRAPPER_H
