

#ifndef ASD2_LABS_2020_HASHMAPSEPARATECHAINING_H
#define ASD2_LABS_2020_HASHMAPSEPARATECHAINING_H


#include <cstdlib>
#include <vector>
#include <list>
#include <algorithm>

template<typename T>
class HashMapSeparateChaining {

    typedef std::list<T> Bucket;
    typedef std::vector<Bucket> HashMap;
    HashMap hashMap;

    // Valeurs par défaut
    size_t M = 2;
    size_t N = 0;

private:
    size_t hash(T key, size_t m) {
        return std::hash<T>()(key) % m;
    }
    void realloc(size_t newM){
        size_t hashCalcul;
        HashMap hashMapNew(newM);
        for (size_t i = 0; i < hashMap.size(); ++i) {
            for (auto j = hashMap.at(i).begin(); j != hashMap.at(i).end(); ++j) {
                T k = *j;
                hashCalcul = hash(k, newM);
                hashMapNew.at(hashCalcul).push_front(k);
            }
        }
        hashMap = hashMapNew;
        M = newM;
    }

public:

    HashMapSeparateChaining(){
        hashMap.resize(2);
    }


    void insert(const T &key) {

        if(contains(key))
            return;

        N++;
        size_t occupancy = N / M;

        if (occupancy >= 8) {
            size_t Mnew = M * 2;
            realloc(Mnew);
        }

        size_t hKey = std::hash<T>()(key) % M;

        hashMap.at(hKey).push_front(key);
    }

    bool contains(const T& key) {
        size_t index = hash(key, M);
        return (std::find(hashMap.at(index).begin(), hashMap.at(index).end(), key) != hashMap.at(index).end());
    }

    void erase(const T& key) {
        size_t index = hash(key, M);
        //peut-être utiliser contains:
        auto it = std::find(hashMap.at(index).begin(), hashMap.at(index).end(), key);
        if(it != hashMap.at(index).end()){
            hashMap.at(index).erase(it);
            --N;
            if(N / M <= 2 and M > 2){
                size_t Mnew = M/2;
                realloc( Mnew);
            }
        }
    }

    size_t size() {
        return N;
    }
};

#endif //ASD2_LABS_2020_HASHMAPSEPARATECHAINING_H
