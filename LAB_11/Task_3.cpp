#include <iostream>
#include <list>
using namespace std;
#define SIZE 100
class Hash {
private:
    list<pair<string, string>> table[SIZE];
    
    int hashFunction(const string &key) {
        int sum = 0;
        for (int i=0;i<key.length();i++)
            sum += key[i];
        return sum % SIZE;
    }
public:
    void insert(string key, string data) {
        int index = hashFunction(key);
        for (auto &p : table[index]) {
            if (p.first == key) {
                p.second = data;
                return;
            }
        }
        table[index].push_back({key, data});
    }
    void search(string key) {
        int index = hashFunction(key);
        for (auto &p : table[index]) {
            if (p.first == key) {
                cout << "search key " << key << ": " << p.second << endl;
                return;
            }
        }
        cout<<"Key not found"<<endl;
    }
    void deleteRecord(string key) {
        int index = hashFunction(key);
        for (auto it = table[index].begin(); it != table[index].end(); it++) {
            if (it->first == key) {
                table[index].erase(it);
                cout << "key " <<key<<" deleted"<<endl;
                return;
            }
        }
        cout<<"Key not found"<<endl;
    }
    void display() {
        for (int i = 0; i < SIZE; i++) {
            for (auto &p : table[SIZE]) {
                cout << "index " << i << ": (" << p.first << ", " << p.second << ")\n";
            }
        }
    }
};

int main(){
    Hash h;
    h.insert("AB", "FASTNU");
    h.insert("CD", "CS");
    h.insert("EF", "Engineering");
    h.search("AB");
    h.deleteRecord("EF");
    h.display();
    return 0;
}