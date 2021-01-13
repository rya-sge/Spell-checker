//
// Created by super on 26/12/2020.
//

#ifndef ASD2_LABS_2020_CONTAINER_H
#define ASD2_LABS_2020_CONTAINER_H


#include <functional>

template<typename T>
class C{

    using boolFunction =  std::function<bool(const T& key)>;
    using voidFunction =  std::function<void(const T& key)>;

    const boolFunction containsF;
    const voidFunction insertF;
    const voidFunction eraseF;

public:

    C(const boolFunction &containsFunction, const voidFunction &insertFunction, const voidFunction &eraseFunction)
            : containsF(containsFunction), insertF(insertFunction), eraseF(eraseFunction) {}

    bool contains(const T& key) const{
        return containsF(key);
    }

    void insert(const T& key) const {
        insertF(key);
    }

    void erase(const T& key) const {
        eraseF(key);
    }
};

#endif //ASD2_LABS_2020_CONTAINER_H
