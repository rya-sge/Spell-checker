#ifndef ASD2_LABS_2020_HASHMAPLINEARPROBING_H
#define ASD2_LABS_2020_HASHMAPLINEARPROBING_H

#include <cstdlib>
#include <vector>

template<typename K>
class HashNode{
public:
   // V value;
    K key;

    //Constructor of hashnode
    HashNode(K key)
    {
       // this->value = value;
        this->key = key;
    }
};
template<typename T>
class HashMapLinearProbing {
// Valeurs par défaut
    size_t M = 2;
    size_t N = 0;
    double MAX_FACTOR = 0.5;
    double MIN_FACTOR = 1.0/8;

    typedef std::vector<HashNode<T>> HashMap;
    //typedef std::vector<std::pair<int, T>> HashMap;
    HashMap hashMap;



    const size_t EMPTY_VALUE = 0;

private:
    size_t hash(const T& key) {
        return std::hash<T>()(key) % M;
    }



public:

    void insert(const T& key) {
        if((double)N / M >= MAX_FACTOR){
            // todo realloc
        }

        // find first available index
        size_t index = hash(key);
        while(hashMap.at(index) != NULL && hashMap.at(index).key != key){
            index = (index + 1)%M;
        }
        hashMap.at(index) = new HashNode<T>(key);
    }

    bool contains(const T& key) {
        size_t index = hash(key);
        size_t count = 0;

        while(count != N){
            if(hashMap.at(index) != NULL && hashMap.at(index).value == key)
                return true;
            else if(!hashMap.at(index))
                break;

            index = (index + 1)%M;
            ++count;
        }

    }

    void erase(const T& key) {
        if(!contains(key)) return;
        int i = hash(key);
        while(hashMap.at(i) == NULL || hashMap.at(i).value != key ){
            i = (i + 1) % M;
        }
        delete hashMap.at(i); //Suppression objet pointé
        hashMap.at(i) = NULL;
        i = (i + 1) % M;
        while(hashMap.at(i) != NULL)
        {
            T keyToRedo = hashMap.at(i).value;
            //Value valToRedo = vals[i];
            delete hashMap.at(i); //Suppression objet pointé
            hashMap.at(i) = NULL;
           // vals[i] = null;
            N--;
            insert(keyToRedo);
            i = (i + 1) % M;

        }
        N--;
        if(N > 0 && N <= MIN_FACTOR){
            //resize
        }

    }

    size_t size() {
        return N;
    }
};



#endif //ASD2_LABS_2020_HASHMAPLINEARPROBING_H
