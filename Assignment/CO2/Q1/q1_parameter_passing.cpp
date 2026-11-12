#include <iostream>
using namespace std;

void byValue(long long fee, int percent) {
    fee -= fee * percent / 100;
    cout << "Inside byValue: " << fee << '\n';
}
void byReference(long long& fee, int percent) {
    fee -= fee * percent / 100;
}
void byPointer(long long* fee, int percent) {
    if (fee != nullptr) *fee -= *fee * percent / 100;
}
long long returnNewFee(long long fee, int percent) {
    return fee - fee * percent / 100;
}
int main() {
    long long merit = 45000, sports = 45000, singleParent = 45000;
    byValue(merit, 10);
    byReference(sports, 15);
    byPointer(&singleParent, 25);
    cout << "Stored after value (10%): " << merit << '\n';
    cout << "Stored after reference (15%): " << sports << '\n';
    cout << "Stored after pointer (25%): " << singleParent << '\n';
    merit = returnNewFee(merit, 10);
    cout << "Stored using returned fee (10%): " << merit << '\n';
}
