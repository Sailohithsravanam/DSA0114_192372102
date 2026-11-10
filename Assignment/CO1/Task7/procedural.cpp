#include <iostream>
using namespace std;

int balancePaise = 10000;

bool canTravel(int farePaise) {
    return balancePaise - farePaise >= 5000;
}

void deductFare(int farePaise) {
    if (canTravel(farePaise)) {
        balancePaise -= farePaise;
        cout << "Journey approved. Balance: Rs " << balancePaise / 100.0 << '\n';
    } else {
        cout << "Journey denied. Balance: Rs " << balancePaise / 100.0 << '\n';
    }
}

int main() {
    deductFare(2000);
    deductFare(4000);
    return 0;
}
