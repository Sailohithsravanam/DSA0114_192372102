#include <iostream>
#include <vector>
using namespace std;

int& highest(int a[], int n) {
    int best=0;
    for(int i=1;i<n;++i) if(a[i]>a[best]) best=i;
    return a[best];
}
const int& highestConst(const int a[], int n) {
    int best=0;
    for(int i=1;i<n;++i) if(a[i]>a[best]) best=i;
    return a[best];
}
int highestCopy(const int a[], int n) {
    int best=0;
    for(int i=1;i<n;++i) if(a[i]>a[best]) best=i;
    return a[best];
}
int highestIndex(const int a[], int n) {
    int best=0;
    for(int i=1;i<n;++i) if(a[i]>a[best]) best=i;
    return best;
}
// Deliberately unsafe example. Never call this function.
int& danglingReference() {
    int local=9;
    return local; // compiler should warn: reference to local variable returned
}
int main() {
    int marks[]={78,91,85,88};
    cout << "Highest before: " << highest(marks,4) << '\n';
    highest(marks,4) += 2;
    cout << "Highest after +2: " << highest(marks,4) << '\n';
    cout << "Const reference: " << highestConst(marks,4) << '\n';
    cout << "Copy: " << highestCopy(marks,4) << '\n';
    int i=highestIndex(marks,4);
    cout << "Index: " << i << ", value: " << marks[i] << '\n';
    int* p=&marks[i]; ++(*p);
    cout << "After pointer update: " << marks[i] << '\n';

    vector<int> values={10,20,30};
    int savedIndex=1;
    values.push_back(40); // index remains usable; old references/pointers may invalidate on reallocation
    cout << "Vector value reacquired by index: " << values[savedIndex] << '\n';
}
