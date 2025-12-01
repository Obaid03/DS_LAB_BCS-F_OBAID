#include <iostream>
using namespace std;
#define SIZE 100
class Node{
public:
    int sum;
    int a, b;
    Node* next;
    Node(int s, int x, int y){
        sum = s;
        a = x;
        b = y;
        next = nullptr;
    }
};
class HashTable{
private:
    Node* table[SIZE];
    int hashFunction(int key){
        return key % SIZE;
    }
public:
    HashTable(){
        for(int i=0;i<SIZE;i++)
            table[i] = nullptr;
    }
    
    Node* find(int sum){
        int index = hashFunction(sum);
        Node* current = table[index];
        while (current != nullptr){
            if (current->sum == sum)
                return current;
            current = current->next;
        }
        return nullptr;
    }
    
    void insert(int sum, int a, int b){
        int index = hashFunction(sum);
        Node* newNode = new Node(sum, a, b);
        newNode->next = table[index];
        table[index] = newNode;
    }
};

void findPairs(int arr[], int n){
    HashTable hash;
    
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            int sum = arr[i] + arr[j];
            Node* result = hash.find(sum);
            
            if(result != nullptr){
                cout<< arr[i] << ", " << arr[j] << ") and (" << result->a << ", " << result->b<<endl;
                return;
            }
            hash.insert(sum, arr[i], arr[j]);
        }
    }
    cout<<"Key not found"<<endl;
}

int main() {
    int arr1[] = {3, 4, 7, 1, 2, 9, 8};
    findPairs(arr1, 7);
    int arr2[] = {3, 4, 7, 1, 12, 9};
    findPairs(arr2, 6);
    int arr3[] = {65, 30, 7, 90, 1, 9, 8};
    findPairs(arr3, 7);
    return 0;
}