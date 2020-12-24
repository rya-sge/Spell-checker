//
// Created by super on 23/12/2020.
//

#ifndef ASD2_LABS_2020_HASHMAPWRAPPER_H
#define ASD2_LABS_2020_HASHMAPWRAPPER_H


template<typename T>
class HashMapWrapper {

public:

    virtual void insert(const T& key) = 0;

    virtual bool contains(const T& key) const = 0;

    virtual bool erase(const T& key) = 0;

    virtual size_t size() const = 0;

    virtual size_t max_size() const = 0;

    virtual double getMaxFactor() const = 0;

    virtual double getMinFactor() const = 0;

    virtual size_t getMaxCoefFactor() const = 0;

    virtual size_t getMinCoefFactor() const = 0;

    virtual size_t getMinValueForM() const = 0;
};



#endif //ASD2_LABS_2020_HASHMAPWRAPPER_H
