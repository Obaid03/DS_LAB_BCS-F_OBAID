#include <iostream>
using namespace std;

class Product {
public:
    string pname;
    float price;
    string detail;
    bool instock;
    Product() {
        pname = "";
        price = 0;
        detail = "";
        instock = false;
    }
};
void swapItem(Product &a, Product &b) {
    Product t = a;
    a = b;
    b = t;
}
int divide(Product p[], int l, int r) {
    float pivot = p[r].price;
    int i = l - 1;
    for (int j = l; j < r; j++) {
        if (p[j].price < pivot) {
            i++;
            swapItem(p[i], p[j]);
        }
    }
    swapItem(p[i + 1], p[r]);
    return i + 1;
}
void quick(Product p[],int l,int r){
    if (l >= r) return;
    int mid = divide(p, l, r);
    quick(p, l, mid - 1);
    quick(p, mid + 1, r);
}

int main(){
    Product items[3];
    cout << "Enter Product Name,Price,Description,Availability"<<endl;
    for (int i = 0; i < 3; i++) {
        cin >> items[i].pname;
        cin >> items[i].price;
        cin.ignore();
        getline(cin, items[i].detail);
        cin >> items[i].instock;
    }
    quick(items, 0, 2);
    cout << "Products Sorted by Price"<<endl;
    for (int i = 0; i < 3; i++) {
        cout << items[i].pname << "  " 
             << items[i].price << "  "
             << items[i].detail << "  "
             << (items[i].instock ? "Available" : "Not Available") 
             << endl;
    }
    return 0;
}