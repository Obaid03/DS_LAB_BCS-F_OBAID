#include <iostream>
using namespace std;

class MaxHeap{
    private:
        int heap[50];
        int size;
    public:
        MaxHeap(){
            size=0;
        }   
        int right(int i){
            return (2*i)+2;
        } 
        int left(int i){
            return (2*i)+1;
        } 
        int parent(int i){
            return(i-1)/2;
        }
        void insert(int value){
            if(size==50){
                cout<<"Heap OverFlow"<<endl;
                return;
            }
            heap[size]=value;
            heapify_up(size);
            size++;
        }
        void heapify_up(int index){
            while(index!=0 && heap[index] > heap[parent(index)]){
                swap(heap[index], heap[parent(index)]);
                index = parent(index);
            }
        }
        void heapify_down(int index){
            int largest=index;
            int l = left(index);
            int r = right(index);

            if(l<size && heap[l] > heap[largest]) largest = l;
            if(r<size && heap[r] > heap[largest]) largest = r;

            if(largest != index){
                swap(heap[index], heap[largest]);
                heapify_down(largest);
            }
        }

        void Display(){
            for(int i=0; i<size; i++){
                cout << heap[i] << " ";
            }
            cout << endl;
        }
};

int main(){
    int arr[] = {1, 23, 12, 9, 30, 2, 50};
    int n = 7;
    MaxHeap h1;
    for(int i = 0; i < n; i++){
        h1.insert(arr[i]);
    }
    cout << "Converted ";
    h1.Display();
    return 0;
}
