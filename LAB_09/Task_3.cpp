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

    //caculatating height
    int getHeight(Node* p){
        if (p == nullptr) return 0;
        int heightL=getHeight(p->left);
        int heightR=getHeight(p->right);
        return heightR>heightL?heightR+1:heightL+1;
    }

    // bf
    int getBF(Node* p) {
        if (p == nullptr) return 0;
        int heightL=getHeight(p->left);
        int heightR=getHeight(p->right);
        return heightL-heightR;
    }

    void updateHeight(Node* p){
        p->height = max(getHeight(p->left), getHeight(p->right)) + 1;
    }

    // rr
    Node* rotateLeft(Node* x){
        Node* y = x->right;
        Node* t = y->left;

        y->left = x;
        x->right = t;

        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // ll
    Node* rotateRight(Node* x){
        Node* y = x->left;
        Node* t = y->right;

        y->right = x;
        x->left = t;

        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* insertNode(Node* p, int value){
        if (p == nullptr)
            return new Node(value);

        if (value < p->key)
            p->left = insertNode(p->left, value);
        else
            p->right = insertNode(p->right, value);

        updateHeight(p);

        int bf = getBF(p);

        // LL 
        if (bf > 1 && value < p->left->key)
            return rotateRight(p);

        // RR 
        if (bf < -1 && value > p->right->key)
            return rotateLeft(p);

        // LR 
        if (bf > 1 && value > p->left->key){
            p->left = rotateLeft(p->left);
            return rotateRight(p);
        }

        // RL
        if (bf < -1 && value < p->right->key){
            p->right = rotateRight(p->right);
            return rotateLeft(p);
        }

        return p;
    }

    void inorder(Node* p){
        if (p == nullptr) return;
        inorder(p->left);
        cout << p->key << " ";
        inorder(p->right);
    }

    void print(Node* p){
        if (p == nullptr) return;
        print(p->left);

        cout << "Node: " << p->key
             << "Height " << p->height
             << "BF " << getBF(p) << endl;

        print(p->right);
    }
    AVL(){
        root = nullptr;
    }
    void insert(int value){
        root = insertNode(root, value);
    }
    void display(){
        inorder(root);
        cout << endl;
    }
    void showBF(){
        print(root);
    }
    int treeHeight(){
        return getHeight(root);
    }
};

int main(){
    AVL tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    cout << "Inorder Traversal "<<endl;
    tree.display();
    cout << "Balance Factors "<<endl;
    tree.showBF();
    cout << "Tree Height " << tree.treeHeight() << endl;
    cout << "Inserting 12  "<<endl;
    tree.insert(12);
    cout << "Inorder Traversal ";
    tree.display();
    cout << "Balance Factors: "<<endl;
    tree.showBF();
    cout << "Tree Height " << tree.treeHeight() << endl;
    return 0;
}
