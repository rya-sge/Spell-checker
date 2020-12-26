//
// Created by david on 23.12.20.
// Hacked by mike
//

#ifndef ASD2_LABS_2020_TERNARYSEARCHTREE_H
#define ASD2_LABS_2020_TERNARYSEARCHTREE_H

#include <string>
#include <limits>

class TST{
private:

    static const size_t  NOT_ASSIGNED = std::numeric_limits<size_t>::max();

    struct Node{
        size_t val = NOT_ASSIGNED;
        char c;
        Node* left;
        Node* mid;
        Node* right;
    };

    Node* root;

    Node* put(Node* x, std::string key, size_t val,  size_t d){
        char c = key.at(d);
        if(x == nullptr){
            x = new Node();
            x->c = c;
        }
        if(c < x->c)
            x->left = put(x->left, key, val, d);
        else if(c > x->c)
            x->right = put(x->right, key, val, d);
        else if(d < key.length() - 1)
            x->mid = put(x->mid, key, val, d+1);
        else x->val = val;
        return x;
    }

    Node* get(Node* x, std::string key, size_t d) const{
        if(x == nullptr) return nullptr;
        char c = key.at(d);
        if (c < x->c) return get(x->left,key,d);
        else if (c > x->c) return get(x->right,key,d);
        else if (d < key.length() - 1) return get(x->mid,key,d+1);
        else return x;
    }

public:
    TST() : root(nullptr) { };
    void put(std::string key, size_t val){
        root = put(root, key, val, 0);
    }
    bool contains(std::string key) const{
        return get(key) != NOT_ASSIGNED;
    }
    size_t get(std::string key) const{
        Node* x = get(root, key, 0);
        if (x == nullptr) return NOT_ASSIGNED;
        return x->val;
    }

};


#endif //ASD2_LABS_2020_TERNARYSEARCHTREE_H
