#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;
    int roll;
    int score;

    Student() {
        name = "";
        roll = 0;
        score = 0;
    }

    Student(string n, int r, int s) {
        name = n;
        roll = r;
        score = s;
    }
};

class Node {
public:
    Student data;
    Node *left, *right;
    Node(Student s): data(s) {
        left = right = NULL;
    }
};

class BSTree {
private:
    Node *root;

    Node* insertNode(Node* curr, Student s){
        if(curr == NULL) return new Node(s);

        if(s.name < curr->data.name)
            curr->left = insertNode(curr->left, s);
        else
            curr->right = insertNode(curr->right, s);

        return curr;
    }

    bool searchNode(Node* curr, string n){
        if(curr == NULL) return false;
        if(n == curr->data.name) return true;

        if(n < curr->data.name)
            return searchNode(curr->left, n);
        return searchNode(curr->right, n);
    }

    Node* minNode(Node* curr){
        while(curr->left != NULL) curr = curr->left;
        return curr;
    }

    Node* deleteLow(Node* curr, int limit){
        if(curr == NULL) return curr;

        curr->left = deleteLow(curr->left, limit);

        if(curr->data.score < limit){
            if(curr->left == NULL){
                Node* r = curr->right;
                delete curr;
                return r;
            }
            if(curr->right == NULL){
                Node* l = curr->left;
                delete curr;
                return l;
            }
            Node* temp = minNode(curr->right);
            curr->data = temp->data;
            curr->right = deleteLow(curr->right, limit);
            return curr;
        }

        curr->right = deleteLow(curr->right, limit);
        return curr;
    }

    void inorder(Node* curr){
        if(curr == NULL) return;
        inorder(curr->left);
        cout << curr->data.name << "  Roll:" << curr->data.roll
             << "  Score:" << curr->data.score << "\n";
        inorder(curr->right);
    }

    void findMax(Node* curr, Student &best){
        if(curr == NULL) return;
        if(curr->data.score > best.score) best = curr->data;
        findMax(curr->left, best);
        findMax(curr->right, best);
    }

public:
    BSTree(){
        root = NULL;
    }

    void insert(Student s){
        root = insertNode(root, s);
    }

    bool search(string n){
        return searchNode(root, n);
    }

    void deleteLowScore(int limit){
        root = deleteLow(root, limit);
    }

    Student getMax(){
        Student best("",0,-1);
        findMax(root, best);
        return best;
    }

    void display(){
        inorder(root);
    }
};

int main(){
    BSTree t;

    Student arr[10] = {
        Student("Ali",1,12),
        Student("Ahmed",2,5),
        Student("Bilal",3,20),
        Student("Omer",4,8),
        Student("Saad",5,17),
        Student("Omar",6,9),
        Student("Saadi",7,25),
        Student("Hamza",8,14),
        Student("Farroq",9,30),
        Student("ABD",10,7)
    };

    int pick[7]={0,2,4,5,6,7,8};
    for(int i=0;i<7;i++)
        t.insert(arr[pick[i]]);

    t.display();

    if(t.search("Saad"))
        cout<<"Found\n";
    else
        cout<<"Not found\n";

    t.deleteLowScore(10);
    t.display();

    Student best = t.getMax();
    cout<<"Max Score: "<<best.name<<" ("<<best.score<<")";

    return 0;
}