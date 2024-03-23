#include <iostream>
using namespace std;

int main() {

    /*
    cout << "Hello, World!" << endl;
    
    for (int i=0; i<4; i++) {
        cout << i << endl;
    }
    
    string fruits[] = {"apple", "banana", "cherry", "guava"};
    for (int i=0; i<4; i++) {
        cout << "Fruit at index: " << i  << ": " << fruits[i] << endl;
    }    

    // dynamic array creation
    cout << "Entire desired array size: ";
    int n;
    cin >> n;
    int* arr = new int[n];
    std::fill_n(arr, n, 0); // fill array with zeros
    */

    int originalVar = 5;
    int& refVar = originalVar;
    int* ptrVar = &originalVar;

    cout << "Original variable stores: " << originalVar << ", Address: " << &originalVar << endl;
    cout << "Reference variable stores: " << refVar << ", Address: " << &refVar << endl;
    cout << "Pointer variable stores: " << ptrVar << ", Pointer adress stores: " << *ptrVar << endl;

    return 0;
}