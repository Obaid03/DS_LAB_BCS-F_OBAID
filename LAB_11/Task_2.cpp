#include <iostream>
using namespace std;
#define SIZE 100
class Node{
public:
    string key;
    string data;
    Node* next;
    Node(string k, string v){
        key = k;
        data = v;
        next = nullptr;
    }
};
class HashTable{
private:
    Node* table[SIZE];
    int hashFunction(const string &key){
        int sum = 0;
        for (int i=0;i<key.length();i++)
            sum += key[i];
        return sum % SIZE;
    }
public:
    HashTable(){
        for(int i = 0;i<SIZE;i++)
            table[i] = nullptr;
    }
    void insert(string key, string data) {
    int index = hashFunction(key);
    Node* current = table[index];
    while (current != nullptr) {
        if (current->key == key) {
            current->data = data;
            return;
        }
        current = current->next;
    }
    Node* newNode = new Node(key, data);
    newNode->next = table[index];
    table[index] = newNode;
}

void search(string key) {
    int index = hashFunction(key);
    Node* current = table[index];
    while (current != nullptr) {
        if (current->key == key) {
            cout << "search key " << key << ": " << current->data << endl;
            return;
        }
        current = current->next;
    }
        cout<<"Key not found"<<endl;
}

void print() {
    for (int i = 0; i < SIZE; i++) {
        Node* current = table[i];
        while (current != nullptr) {
            cout << "index " << i << ": (" << current->key << ", " << current->data << ")\n";
            current = current->next;
        }
    }
}

void delete_R(string key) {
    int index = hashFunction(key);
    Node* current = table[index];
    Node* prev = nullptr;
    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            cout << "key " << key << " deleted"<<endl;
            return;
        }
        prev = current;
        current = current->next;
    }
    cout<<"Key not found"<<endl;
}
};
int main() {
    HashTable dictionary;
    
    dictionary.insert("AB", "FASTNU");
    dictionary.insert("CD", "CS");
    dictionary.insert("EF", "Engineering");
    dictionary.search("AB");
    dictionary.delete_R("EF");
    dictionary.print();
    return 0;
}