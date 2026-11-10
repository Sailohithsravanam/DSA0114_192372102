#include <iostream>
using namespace std;
int main() {
    int total = 5, count = 2;
    double integerDivision = total / count;
    double realDivision = static_cast<double>(total) / count;
    int wholeRupees = 20;
    double rupees = wholeRupees; // int-to-double conversion
    int narrowed = static_cast<int>(12.89); // explicit narrowing
    int safeValue{12}; // brace initialization
    int signedValue = -1;
    unsigned int unsignedValue = 1;
    cout << "5 / 2 assigned to double: " << integerDivision << '\n';
    cout << "5.0 / 2: " << realDivision << '\n';
    cout << "Converted rupees: " << rupees << '\n';
    cout << "Narrowed value: " << narrowed << '\n';
    cout << "Brace initialized value: " << safeValue << '\n';
    cout << "Signed value: " << signedValue
         << ", unsigned value: " << unsignedValue << '\n';
    cout << "Signed/unsigned comparison (implementation conversion rules apply): "
         << (signedValue < unsignedValue) << '\n';
    return 0;
}
