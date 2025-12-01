#include <iostream>
using namespace std;
#define SIZE 15

class Student{
public:
    int rollNumber;
    string name;
    bool occupied;
    
    Student(){
        rollNumber = -1;
        name = "";
        occupied = false;
    }
};
class StudentHashTable{
private:
    Student table[SIZE];
    
    int hashFunction(int rollNumber){
        return rollNumber % SIZE;
    }
public:
    StudentHashTable(){
        for(int i=0;i<SIZE;i++){
            table[i].occupied = false;
        }
    }
    
    void InsertRecord(int rollNumber, string name){
        int index = hashFunction(rollNumber);
        int attempt = 0;
        while(table[index].occupied && attempt < SIZE){
            attempt++;
            index = (hashFunction(rollNumber) + attempt * attempt) % SIZE;
        }
        if(attempt < SIZE){
            table[index].rollNumber = rollNumber;
            table[index].name = name;
            table[index]. occupied = true;
        } else{
            cout << "Table full"<<endl;
        }
    }
    void SearchRecord(int rollNumber){
        int index = hashFunction(rollNumber);
        int attempt = 0;
        
        while(attempt < SIZE) {
            if(table[index].occupied && table[index].rollNumber == rollNumber){
                cout << "Student found: " << table[index].name << endl;
                return;
            }
            attempt++;
            index = (hashFunction(rollNumber) + attempt * attempt) % SIZE;
        }
        
        cout<<"Key not found"<<endl;
    }
    
    void display(){
        for(int i=0;i<SIZE;i++){
            if(table[i].occupied){
                cout << "Index " << i << ": Roll=" << table[i].rollNumber << ", Name=" << table[i]. name << endl;
            }
        }
    }
};

int main() {
    StudentHashTable st;
    st.InsertRecord(101, "Ali");
    st.InsertRecord(116, "Ahmed");
    st.InsertRecord(131, "Pasha");
    st.InsertRecord(102, "Shama");
    st.InsertRecord(117, "Hasan");
    st.display();
    cout << "Searching"<<endl;;
    st.SearchRecord(116);
    st.SearchRecord(131);
    st.SearchRecord(999);
    return 0;
}