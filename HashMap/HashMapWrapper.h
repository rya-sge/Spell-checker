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


    virtual void insert(const T& key) = 0;

    virtual bool contains(const T& key) const = 0;

    virtual bool erase(const T& key) = 0;

    virtual size_t size() const = 0;

    virtual size_t max_buckets() const = 0;

    virtual double getMaxFactor() const = 0;

    virtual double getMinFactor() const = 0;

    virtual size_t getMulCoefFactor() const = 0;

    virtual size_t getDivCoefFactor() const = 0;

    virtual size_t getMinValueForM() const = 0;
};



#endif //ASD2_LABS_2020_HASHMAPWRAPPER_H
