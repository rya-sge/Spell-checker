//
// Created by super on 23/12/2020.
//

#ifndef ASD2_LABS_2020_HASHMAPWRAPPER2_H
#define ASD2_LABS_2020_HASHMAPWRAPPER2_H


#include <unordered_set>

template<typename T>
class HashMapWrapper2 {

    std::unordered_set<T> hashMap;

public:

    virtual void insert(const T& key){}

    virtual bool contains(const T& key){}

    virtual bool erase(const T& key){}

    virtual size_t size(){}

    virtual size_t max_size(){}

    virtual double getMaxFactor(){}

    virtual double getMinFactor() {}

    virtual size_t getMaxCoefFactor() {}

    virtual size_t getMinCoefFactor(){}
};



#endif //ASD2_LABS_2020_HASHMAPWRAPPER2_H
