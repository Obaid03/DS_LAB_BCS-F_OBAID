#include<iostream>
using namespace std;

class Node {
public:
    int key;
    Node *left;
    Node *right;

    Node(int k) : key(k) {
        left = right = NULL;
    }
};

class BSTree {
private:
    Node *head;
    int nodeCount;
    Node* insert(Node *curr, int value){
        if(curr == NULL){
            return new Node(value);
        }

        if(value < curr->key){
            curr->left = insert(curr->left, value);
        }
        else if(value > curr->key){
            curr->right = insert(curr->right, value);
        }
        return curr;
    }

    public:

    BSTree(){
        head = NULL;
        nodeCount = 0;
    }
    void inorder(Node *curr){
        if(curr != NULL){
            inorder(curr->left);
            cout << curr->key << " ";
            inorder(curr->right);
        }
    }

    Node* minimum(Node *curr) {
        while(curr && curr->left != NULL){
            curr = curr->left;
        }
        return curr;
    }

    Node* deleteNode(Node *curr, int value) {
        if(curr == NULL) return curr;

        if(value < curr->key)
            curr->left = deleteNode(curr->left, value);

        else if(value > curr->key)
            curr->right = deleteNode(curr->right, value);

        else {
            if (curr->left == NULL && curr->right == NULL) {
                delete curr;
                return NULL;
            }
            else if(curr->left == NULL) {
                Node *temp = curr->right;
                delete curr;
                return temp;
            }
            else if(curr->right == NULL) {
                Node *temp = curr->left;
                delete curr;
                return temp;
            }
            else{
                Node *temp = minimum(curr->right);
                curr->key = temp->key;
                curr->right = deleteNode(curr->right, temp->key);
            }
        }
        return curr;
    }

    bool SearchNode(Node *curr, int value) {
        if(curr == NULL) return false;

        if(curr->key == value)
            return true;
        else if(value < curr->key)
            return SearchNode(curr->left, value);
        else
            return SearchNode(curr->right, value);
    }

    void insert(int value) {
        head = insert(head, value);
    }

    void display(){
        cout << "Disaplaying BST"<<endl;
        inorder(head);
    }

    void Delete(int value) {
        head = deleteNode(head, value);
    }

    bool search(int value) {
        return SearchNode(head, value);
    }
};

int main(){
    BSTree tree;

    tree.insert(23);
    tree.insert(12);
    tree.insert(2);
    tree.insert(54);
    tree.insert(26);
    tree.insert(43);
    tree.display();
    tree.Delete(2);
    tree.display();
    cout <<tree.search(2);
}