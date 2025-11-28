#include <iostream>
using namespace std;
struct Node {
    int val;
    Node* next;
    Node(int x) : val(x), next(NULL) {}
};
void addNode(Node*& h, int x) {
    if (!h) {
        h = new Node(x);
        return;
    }
    Node* t = h;
    while (t->next)
        t = t->next;
    t->next = new Node(x);
}
void clearList(Node* h) {
    while (h) {
        Node* p = h;
        h = h->next;
        delete p;
    }
}

int biggest(int a[], int n) {
    int m = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > m)
            m = a[i];
    return m;
}

void radixsort(int a[], int n, bool asc) {
    int mx = biggest(a, n);
    int p = 1;

    while (mx / p > 0) {
        Node* box[10];
        for (int i = 0; i < 10; i++)
            box[i] = NULL;

        for (int i = 0; i < n; i++) {
            int d = (a[i] / p) % 10;
            addNode(box[d], a[i]);
        }

        int k = 0;

        if (asc) {
            for (int i = 0; i < 10; i++) {
                Node* t = box[i];
                while (t) {
                    a[k++] = t->val;
                    t = t->next;
                }
                clearList(box[i]);
            }
        }
        else {
            for (int i = 9; i >= 0; i--) {
                Node* t = box[i];
                while (t) {
                    a[k++] = t->val;
                    t = t->next;
                }
                clearList(box[i]);
            }
        }

        p *= 10;
    }
}

void Display(int a[], int n) {
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

int main() {
    int arr[] = {36,987,654,2,20,99,456,957,555,420,66,3};
    int n = 12;
    int* A = new int[n];
    int* B = new int[n];
    for (int i = 0; i < n; i++)
        A[i] = B[i] = arr[i];

    radixsort(A, n, true);
    radixsort(B, n, false);

    cout << "\nAscending : ";
    Display(A, n);

    cout << "Descending: ";
    Display(B, n);

    delete[] A;
    delete[] B;
    return 0;
}
