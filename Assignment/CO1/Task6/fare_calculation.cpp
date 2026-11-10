#include <iostream>
#include <iomanip>
using namespace std;
int fareForZone(int zone) {
    switch (zone) {
        case 1: return 1000; // Inner, paise
        case 2: return 2000; // Middle
        case 3: return 3000; // Outer
        default: return -1;
    }
}

bool isPeak(int hour) {
    return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
}

int main() {
    int balance = 10000; // Rs 100 in paise
    const int minimumBalance = 5000;
    int zones[] = {1, 2, 2};
    int hours[] = {10, 8, 18};

    for (int i = 0; i < 3; ++i) {
        int fare = fareForZone(zones[i]);
        if (fare < 0) {
            cout << "Invalid zone\n";
            continue;
        }
        if (isPeak(hours[i])) fare = fare * 120 / 100;

        if (balance - fare >= minimumBalance) {
            balance -= fare;
            cout << "Fare Rs " << fixed << setprecision(2) << fare / 100.0
                 << " balance Rs " << balance / 100.0 << '\n';
        } else {
            cout << "Denied (low balance) balance Rs "
                 << balance / 100.0 << '\n';
        }
    }
    return 0;
}
