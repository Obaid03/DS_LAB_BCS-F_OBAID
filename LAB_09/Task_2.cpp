#include <iostream>
using namespace std;

class Node{
public:
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int k){
        key = k;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class AVL {
    Node* root;
    public:

    // height
    int getHeight(Node* p){
        if (p == nullptr) return 0;
        int hL = getHeight(p->left);
        int hR = getHeight(p->right);
        return hL > hR ? hL + 1 : hR + 1;
    }

    // balance factor
    int getBF(Node* p){
        if (p == nullptr) return 0;
        int hL = getHeight(p->left);
        int hR = getHeight(p->right);
        return hL - hR;
    }

    void updateHeight(Node* p){
        p->height = (getHeight(p->left) > getHeight(p->right)
                     ? getHeight(p->left)
                     : getHeight(p->right)) + 1;
    }

    // RR
    Node* rotateLeft(Node* x){
        Node* y = x->right;
        Node* t = y->left;
        y->left = x;
        x->right = t;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // LL
    Node* rotateRight(Node* x){
        Node* y = x->left;
        Node* t = y->right;

        y->right = x;
        x->left = t;

        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* insertNode(Node* p, int val){
        if (p == nullptr)
            return new Node(val);

        if (val < p->key)
            p->left = insertNode(p->left, val);
        else
            p->right = insertNode(p->right, val);

        updateHeight(p);

        int bf = getBF(p);

        // LL
        if (bf > 1 && val < p->left->key)
            return rotateRight(p);

        // RR
        if (bf < -1 && val > p->right->key)
            return rotateLeft(p);

        // LR
        if (bf > 1 && val > p->left->key) {
            p->left = rotateLeft(p->left);
            return rotateRight(p);
        }

        // RL
        if (bf < -1 && val < p->right->key) {
            p->right = rotateRight(p->right);
            return rotateLeft(p);
        }

        return p;
    }
    void inorder(Node* p) {
        if (p == nullptr) return;
        inorder(p->left);
        cout << p->key << " ";
        inorder(p->right);
    }
    AVL(){
        root = nullptr;
    }
    void insert(int val){
        root = insertNode(root, val);
    }
    void rotateRootLeft(){
        if (root != nullptr)
            root = rotateLeft(root);
    }
    void display(){
        inorder(root);
        cout << endl;
    }
};

int main(){
    AVL tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    cout << "AVL TREE " << endl;
    tree.display();
    cout << "Inserting 55" << endl;
    tree.insert(55);
    cout << "AVL Tree After Insertion" << endl;
    tree.display();
    cout << "Applying LEFT ROTATION" << endl;
    tree.rotateRootLeft();
    cout << "FINAL AVL TREE"  << endl;
    tree.display();
    return 0;
}