//
// Created by super on 23/12/2020.
//

#ifndef ASD2_LABS_2020_HASHMAPWRAPPER_H
#define ASD2_LABS_2020_HASHMAPWRAPPER_H


template<typename T>
class HashMapWrapper {

public:

    virtual void insert(const T& key) = 0;

    virtual bool contains(const T& key) = 0;

    virtual bool erase(const T& key) = 0;

    virtual size_t size() = 0;

    virtual size_t max_size() = 0;

    virtual double getMaxFactor() = 0;

    virtual double getMinFactor() = 0;

    virtual size_t getMaxCoefFactor() = 0;

    virtual size_t getMinCoefFactor() = 0;

    virtual size_t getMinValueForM() = 0;
};



#endif //ASD2_LABS_2020_HASHMAPWRAPPER_H
