//
// Created by david on 23.12.20.
// Hacked by mike
//

#ifndef ASD2_LABS_2020_TERNARYSEARCHTREE_H
#define ASD2_LABS_2020_TERNARYSEARCHTREE_H

#include <string>
#include <limits>
#include <list>

class TST{
private:

    static const size_t  NOT_ASSIGNED = std::numeric_limits<size_t>::max();

    size_t sizeTST = 0;

    struct Node{
        size_t val = NOT_ASSIGNED;
        char c;
        Node* left;
        Node* mid;
        Node* right;
        int nodeHeight;
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
        else{
            if(x->val == NOT_ASSIGNED)
                ++sizeTST;
            x->val = val;
        }
        return restoreBalance(x);
    }

    Node* get(Node* x, std::string key, size_t d) const{
        if(x == nullptr) return nullptr;
        char c = key.at(d);
        if (c < x->c) return get(x->left,key,d);
        else if (c > x->c) return get(x->right,key,d);
        else if (d < key.length() - 1) return get(x->mid,key,d+1);
        else return x;
    }

    void erase(Node* x, std::string key, size_t d, std::list<Node*>& listNodes) {
        listNodes.push_back(x);
        char c = key.at(d);
        if (c < x->c) erase(x->left,key,d,listNodes);
        else if (c > x->c) erase(x->right,key,d,listNodes);
        else if (d < key.length() - 1) erase(x->mid,key,d+1,listNodes);
        else {
            x->val = NOT_ASSIGNED;
            --sizeTST;
            return;
        }
    }

    int height(Node* x) {
        if ( x == nullptr ) return -1;
        return x->nodeHeight;
    }

    void updateNodeHeight(Node* x) {
        x->nodeHeight = std::max(height(x->right),height(x->left)) + 1;
    }

    int balance(Node* x) {
        if(x==nullptr) return 0;
        return height(x->right) - height(x->left);
    }

    Node* rotateLeft(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;

        updateNodeHeight(x);
        updateNodeHeight(y);
        return y;
    }

    Node* rotateRight(Node* x)
    {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;

        updateNodeHeight(x);
        updateNodeHeight(y);
        return y;
    }

    Node* restoreBalance(Node* x)
    {
        if(balance(x) < -1) // right < left-1
        {
            if (balance(x->left)>0) // double rot.
                x->left = rotateLeft( x->left );
            x = rotateRight(x);
        }
        else if( balance(x) > 1) // right > left+1
        {
            if ( balance(x->right) < 0 ) // double rot.
                x->right = rotateRight( x->right );
            x = rotateLeft(x);
        }
        else updateNodeHeight(x); // équilibre ok
        return x;
    }

public:
    TST() : root(nullptr) { };
    void insert(std::string key, size_t val){
        root = put(root, key, val, 0);
    }
    bool contains(std::string key) const{
        Node* x = get(root, key, 0);
        if (x == nullptr) return false;
        return x->val != NOT_ASSIGNED;
    }
    void erase(std::string key){
        if(!contains(key))
            return;
        std::list<Node*> listNodes;
        erase(root, key, 0, listNodes);
        Node* x;
        while(!listNodes.empty()){
            x = listNodes.back();
            listNodes.pop_back();
            if (x->mid == nullptr and x->left == nullptr and x->right == nullptr and x->val == NOT_ASSIGNED){
                delete x->right;
                delete x->mid;
                delete x->left;
                x = nullptr;
            }
            else{
                break;
            }
        }
    }
    size_t size(){
        return sizeTST;
    }


};


#endif //ASD2_LABS_2020_TERNARYSEARCHTREE_H
