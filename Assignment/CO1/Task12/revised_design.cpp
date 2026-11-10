#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class MonthlyPass {
    int zoneA, zoneB;
public:
    MonthlyPass(int a, int b) : zoneA(a), zoneB(b) {}
    bool covers(int zone) const { return zone == zoneA || zone == zoneB; }
};

int baseFare(int zone) {
    switch (zone) {
        case 1: return 1000;
        case 2: return 2000;
        case 3: return 3000;
        case 4: return 6000; // Airport
        default: return -1;
    }
}

bool peak(int h) {
    return (h >= 8 && h < 10) || (h >= 17 && h < 20);
}

int fare(int zone, int hour, bool weekend, bool concession) {
    int amount = baseFare(zone);
    if (amount < 0 || hour < 0 || hour > 23) return -1;
    if (concession) amount /= 2;
    if (weekend) amount = amount * 90 / 100; // Weekend discount replaces peak surcharge
    else if (peak(hour)) amount = amount * 120 / 100;
    return amount;
}

int main() {
    MonthlyPass pass(1, 2);
    cout << fixed << setprecision(2);

    int zone = 2, hour = 18;
    if (pass.covers(zone)) {
        cout << "Monthly Pass: unlimited covered-zone journey, fare Rs 0.00\n";
    } else {
        int amount = fare(zone, hour, false, false);
        cout << "Regular fare: Rs " << amount / 100.0 << '\n';
    }

    cout << "Airport off-peak fare: Rs " << fare(4, 12, false, false) / 100.0 << '\n';
    cout << "Weekend Middle fare: Rs " << fare(2, 18, true, false) / 100.0 << '\n';
    cout << "Weekend discount is not combined with peak surcharge.\n";
    return 0;
}
