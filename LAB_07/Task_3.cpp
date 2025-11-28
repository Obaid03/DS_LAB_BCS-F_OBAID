#include <iostream>
using namespace std;

struct Runner {
    string name;
    int time;
};
void mergeParts(Runner a[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Runner* L = new Runner[n1];
    Runner* R = new Runner[n2];
    for (int i = 0; i < n1; i++)
        L[i] = a[l + i];

    for (int j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].time <= R[j].time) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        a[k] = L[i];
        i++; k++;
    }
    while (j < n2) {
        a[k] = R[j];
        j++; k++;
    }
    delete[] L;
    delete[] R;
}

void mergeSort(Runner a[], int l, int r){
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m + 1, r);
    mergeParts(a, l, m, r);
}
int main(){
    Runner list[10];

    cout << "Enter name and time of 10 runner " << endl;

    for(int i = 0; i < 10; i++){
        cin >> list[i].name >> list[i].time;
    }
    mergeSort(list, 0, 9);
    cout<<"\nTop 5 Fastest Runners\n";
    for (int i = 0; i < 5; i++) {
        cout << list[i].name << "  " << list[i].time << " sec" << endl;
    }
    return 0;
}