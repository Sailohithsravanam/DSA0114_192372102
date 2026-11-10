#include <iostream>
#include <climits>
using namespace std;
int main() {
    bool valid = true;
    char category = 'S';
    int balancePaise = 10000;
    long long totalPaise = 3000000000LL;
    unsigned int passengerCount = 25;
    float approximateFare = 20.5f;
    double exactDisplayFare = 20.50;
    auto peakHour = 8;
    cout << boolalpha;
    cout << "bool: " << valid << " size=" << sizeof(valid) << '\n';
    cout << "char: " << category << " size=" << sizeof(category) << '\n';
    cout << "int paise: " << balancePaise << " size=" << sizeof(balancePaise) << '\n';
    cout << "long long: " << totalPaise << " size=" << sizeof(totalPaise) << '\n';
    cout << "unsigned passengers: " << passengerCount << '\n';
    cout << "float fare: " << approximateFare << '\n';
    cout << "double fare: " << exactDisplayFare << '\n';
    cout << "auto peak hour: " << peakHour << '\n';
    cout << "INT_MAX: " << INT_MAX << '\n';
    cout << "Money should be stored as integer paise to avoid floating-point rounding.\n";
    return 0;
}
