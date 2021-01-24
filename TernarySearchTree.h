/* ---------------------------
Laboratoire : 8 - Correcteur orthographique
Fichier : TernarySearchTree.h
Auteurs : David Pellissier, Michael Ruckstuhl, Ryan Sauge
Date : 23.01.2021

But : Implémentation d'une table de hachage avec sondage linéaire

Compilateur : gcc 9.3.0
--------------------------- */

#ifndef ASD2_LABS_2020_TERNARYSEARCHTREE_H
#define ASD2_LABS_2020_TERNARYSEARCHTREE_H

#include <string>
#include <limits>
#include <list>

class TST{
private:

    static const size_t  NOT_ASSIGNED = std::numeric_limits<size_t>::max();

    size_t sizeTST = 0;

    /**
     * Structure permettant de faire un noeud.
     */
    struct Node{
        size_t val = NOT_ASSIGNED;
        char c;
        Node* left;
        Node* mid;
        Node* right;
        int nodeHeight = 0;
    };

    Node* root;

    /**
     * @brief Appelée par insert aide à linsertion du mot.
     * @param x le noeud courrant.
     * @param key le mot à inserer.
     * @param val la valeur du mot.
     * @param d le numéro de caractère du mot à inserer.
     * @return le noeud équilibré.
     */
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

    /**
     * @brief Renvoie la valeur du mot cherché ou NOT_ASSIGNED si celui-ci n'existe pas.
     * @param x noeud courrant.
     * @param key le mot à obtenir.
     * @param d le numéro de caractère du mot à obtenir.
     * @return la valeur du mot cherché ou NOT_ASSIGNED si celui-ci n'existe pas.
     */
    Node* get(Node* x, std::string key, size_t d) const{
        if(x == nullptr) return nullptr;
        char c = key.at(d);
        if (c < x->c) return get(x->left,key,d);
        else if (c > x->c) return get(x->right,key,d);
        else if (d < key.length() - 1) return get(x->mid,key,d+1);
        else return x;
    }

    Node* deleteLeaf(Node* x){
        if (x != root && x->val == NOT_ASSIGNED && x->mid == nullptr && x->left == nullptr && x->right == nullptr){
            delete x;
            x = nullptr;
        }
        return x;
    }
    /**
     * @brief Fonction appelée par erase public. Aide à supprimer le noeud
     * @param x noeud courant.
     * @param key le mot à supprimer.
     * @param d le numéro de caractère du mot à supprimer.
     */
    Node* deleteElement(Node* x, std::string key, size_t d) {
        if(x == nullptr) return x;
        char c = key.at(d);
        if ( c < x->c )
            x->left = deleteElement(x->left,key,d);
        else if ( c > x->c)
            x->right = deleteElement(x->right,key,d);
        else if (d < key.length() - 1)
            x->mid = deleteElement(x->mid,key,d+1);
        else {
            if(x->val != NOT_ASSIGNED){
                x->val = NOT_ASSIGNED;
                --sizeTST;
            }
            if (deleteLeaf(x) != nullptr){
                return restoreBalance(x);
            }
        }
        return deleteLeaf(x);
    }

    /**
     * @brief Renvoie la taille du noeud. -1 si le noeud est nul.
     * @param x le noeud.
     * @return la taille du noeud. -1 si le noeud est nul.
     * @details fonction reprise des slides "Arbres AVL"
     *          faites par Laura Elena Raileanu, Marc Dikötter
     *          pour le cours ASD2.
     */
    int height(Node* x) {
        if ( x == nullptr ) return -1;
        return x->nodeHeight;
    }

    /**
     * @brief Met à jour la taille d'un noeud.
     * @param x le noeud.
     * @details fonction reprise des slides "Arbres AVL"
     *          faites par Laura Elena Raileanu, Marc Dikötter
     *          pour le cours ASD2.
     */
    void updateNodeHeight(Node* x) {
        x->nodeHeight = std::max(height(x->right),height(x->left)) + 1;
    }

    /**
     * @brief Calcul du déséquilibre à partir d'un noeud.
     * @param x le noeud.
     * @return le déséquilibre
     * @details fonction reprise des slides "Arbres AVL"
     *          faites par Laura Elena Raileanu, Marc Dikötter
     *          pour le cours ASD2.
     */
    int balance(Node* x) {
        if(x==nullptr) return 0;
        return height(x->right) - height(x->left);
    }

    /**
    * @brief Effectue une rotation à gauche par rapport à un noeud.
    * @param x le noeud
    * @return le nouveau noeud
    * @details fonction reprise des slides "Arbres AVL"
    *          faites par Laura Elena Raileanu, Marc Dikötter
    *          pour le cours ASD2.
    */
    Node* rotateLeft(Node* x)
    {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;

        updateNodeHeight(x);
        updateNodeHeight(y);
        return y;
    }

    /**
     * @brief Effectue une rotation à droite par rapport à un noeud.
     * @param x le noeud
     * @return le nouveau noeud
     * @details fonction reprise des slides "Arbres AVL"
     *          faites par Laura Elena Raileanu, Marc Dikötter
     *          pour le cours ASD2.
     */
    Node* rotateRight(Node* x)
    {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;

        updateNodeHeight(x);
        updateNodeHeight(y);
        return y;
    }


    /**
     * @brief Si nécessaire, restauration par rotation
     *        simple ou double selon l’équilibre du
     *        nœud suivant du côté lourd.
     * @param x noeud
     * @return le noeud équilibré
     * @details fonction reprise des slides "Arbres AVL"
     *          faites par Laura Elena Raileanu, Marc Dikötter
     *          pour le cours ASD2.
     */
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

    /**
     * @brief Parcours l'arbre depuis un noeud est vérifie que tous est équilibré depuis ce noeud.
     * @param x le noeud de départ.
     * @return Vrai si rien de désequilibré n'est trouvé. Sinon faux.
     */
    bool isBalanced(Node* x){
        if(x == nullptr){
            return true;
        }
        if((x->left != nullptr) && (x->right != nullptr)){
            int diffHeight = x->right->nodeHeight - x->left->nodeHeight;
            if(diffHeight < -1 or diffHeight > 1)
                return false;
            int maxHeight = std::max( x->right->nodeHeight, x->left->nodeHeight);
            if((x->nodeHeight - maxHeight - 1) != 0)
                return false;
        }
        bool a = true, b = true, c = true;
        if(x->left != nullptr){
            a = isBalanced(x->left);
        }
        if(x->mid != nullptr){
            b = isBalanced(x->mid);
        }
        if(x->right != nullptr){
            c = isBalanced(x->right);
        }
        return a && b && c;
    }

    /**
     * @brief Appelé par le destructeur pour détruire tous les noeuds.
     * @param x le noeud dont les enfants vont être effacé.
     */
    void eraseAll(Node* x){
        if( x == nullptr) return;
        eraseAll( x->right );
        eraseAll( x->mid );
        eraseAll( x->left );
        delete x;
    }

public:

    /**
     * Constructeur de l'arbre
     */
    TST() : root(nullptr) { };

    /**
     * Destructeur de l'arbre
     */
    ~TST(){
        eraseAll(root);
    }

    /**
     * @brief Insère un mot dans l'arbre avec sa valeur.
     * @param key le mot à insérer.
     * @param val la valeur à insérer.
     * @throw invalid_argument si val vaut la même chose que NOT_ASSIGNED.
     */
    void insert(std::string key, size_t val) {
        if (val == NOT_ASSIGNED)
            throw std::invalid_argument("La valeur ne doit pas être la même que NOT_ASSIGNED");
        root = put(root, key, val, 0);
    }

    /**
     * @brief Indique si un mot est contenu dans l'arbre.
     * @param key le mot à vérifier.
     * @return vrai si le mot est contenu dans l'arbre. Si ce n'est pas le cas, faux est renvoyé.
     */
    bool contains(std::string key) const{
        Node* x = get(root, key, 0);
        if (x == nullptr) return false;
        return x->val != NOT_ASSIGNED;
    }

    /**
     * @brief Permet de supprimer un mot de l'arbre.
     *        Supprime les noeuds qui n'ont plus d'utilité.
     * @param key mot à supprimer
     */
    void erase(std::string key){
        deleteElement(root,  key, 0);
    }

    /**
     * @brief   Renvoie la taille (nombre de mots) de l'arbre
     * @return  la taille (nombre de mots) de l'arbre
     */
    size_t size(){
        return sizeTST;
    }

    /**
     * @brief  Permet de savoir si l'arbre est équilibré
     * @return true si l'arbre est équilibré. False si ce n'est pas le cas
     */
    bool isBalanced(){
        return isBalanced(root);
    }

};


#endif //ASD2_LABS_2020_TERNARYSEARCHTREE_H
