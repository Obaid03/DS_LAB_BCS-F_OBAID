#include <iostream>
using namespace std;
#define SIZE 11
class Node {
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
class HashTable {
private:
    Node* table[SIZE];
    int hashFunction(const string &key) {
        int sum = 0;
        for (int i=0;i<key.length();i++)
            sum += key[i];
        return sum / SIZE;
    }
public:
    HashTable(){
        for(int i = 0;i<SIZE;i++)
            table[i] = nullptr;
    }

    void insert(string key,string data) {
        int index = hashFunction(key);
        Node* head = table[index];
        Node* current = head;
        while (current != nullptr) {
            if (current->key == key) {
                current->data = data;
                return;
            }
            current = current->next;
        }
        Node* newNode = new Node(key, data);
        newNode->next = head;
        table[index] = newNode;
    }
    void print() {
        for (int i = 0; i < SIZE; i++) {
            cout << "Bucket[" << i << "]: ";
            Node* current = table[i];
            while (current != nullptr) {
                cout << "(" << current->key << ", " << current->data << ") -> ";
                current = current->next;
            }
            cout << "NULL\n";
        }
    }
};
int main() {
    HashTable myhash;

    myhash.insert("A", "aaaaa");
    myhash.insert("B", "bbbbb");
    myhash.insert("C", "ccccc");
    myhash.insert("A", "zzzzz");

    cout << "Hash Table Content:\n";
    myhash.print();

    return 0;
}