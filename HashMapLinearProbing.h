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

    typedef std::vector<HashNode<T>*> HashMap;

    HashMap *hashMap;

    const size_t EMPTY_VALUE = 0;

private:
    size_t hash(const T& key, size_t m) {
        return std::hash<T>()(key) % m;
    }

    void findPosition(HashMap* hashMap, const T& key, size_t m, size_t& index){
        while(hashMap->at(index) != NULL && hashMap.at(index).key != key){
            index = (index + 1) % m;
        }
    }


    void realloc(size_t newM){
        HashMap *newHashMap  = new HashMap(newM);

        for(HashNode<T> *ptr: *hashMap)
        {
            if(ptr != NULL){
                T key = ptr->key;
                // insert values into the new table
                size_t index = hash(key, newM);
                findPosition(newHashMap, key,newM, index);
                newHashMap->at(index) = ptr;
            }

        }
        // remarque: peut mieux faire avec l'allocation dynamique ?
        HashMap *oldHashMap = hashMap;
        hashMap = newHashMap;
        delete oldHashMap;

        M = newM;
    }

public:
    HashMapLinearProbing(){
        hashMap = new HashMap(M);
    }

    ~HashMapLinearProbing(){
        for( HashNode<T> *ptr : *hashMap){
            delete ptr;
        }
        delete hashMap;
    }

    void insert(const T& key) {
        if((double)N / M >= MAX_FACTOR){
            realloc(M*2);
        }

        // find first available index
        size_t index = hash(key, M);
        findPosition(hashMap, key, M, index);
        hashMap->at(index) = new HashNode<T>(key);
        ++N;
    }

    bool contains(const T& key) {
        size_t index = hash(key, M);
        size_t count = 0;

        while(count != N){
            if(hashMap->at(index) != NULL && hashMap->at(index)->key == key)
                return true;
            else if(!hashMap->at(index))
                break;

            index = (index + 1)%M;
            ++count;
        }

        return false;
    }

    void erase(const T& key) {
        if(!contains(key)) return;
        int i = hash(key, M);
        while(hashMap->at(i) == NULL || hashMap->at(i)->key != key ){
            i = (i + 1) % M;
        }
        delete hashMap->at(i); //Suppression objet pointé
        hashMap->at(i) = NULL;
        i = (i + 1) % M;
        while(hashMap->at(i) != NULL)
        {
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
        if(N > 0 && N <= MIN_FACTOR){
            realloc(M / 2);
        }

    }

    size_t size() {
        return N;
    }
};



#endif //ASD2_LABS_2020_HASHMAPLINEARPROBING_H
