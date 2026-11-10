#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int baseFarePaise(int zone) {
    switch (zone) {
        case 1: return 1000;
        case 2: return 2000;
        case 3: return 3000;
        default: return -1;
    }
}

bool peakHour(int h) {
    return (h >= 8 && h < 10) || (h >= 17 && h < 20);
}

int calculateFare(int zone, int hour, bool concession) {
    int fare = baseFarePaise(zone);
    if (fare < 0 || hour < 0 || hour > 23) return -1;
    if (concession) fare = fare / 2; // Assumption: concession before peak
    if (peakHour(hour)) fare = (fare * 120 + 50) / 100;
    return fare;
}

int main() {
    int balance = 10000;
    const int minimumBalance = 5000;

    struct Test { int zone, hour; bool concession; const char* label; };
    Test tests[] = {
        {1, 10, false, "Inner off-peak"},
        {2, 8, false, "Middle peak"},
        {3, 17, false, "Outer peak"},
        {1, 7, true, "Inner concession"},
        {4, 12, false, "Invalid zone"}
    };

    for (const auto& t : tests) {
        int fare = calculateFare(t.zone, t.hour, t.concession);
        cout << t.label << ": ";
        if (fare < 0) {
            cout << "Invalid input\n";
        } else if (balance - fare >= minimumBalance) {
            balance -= fare;
            cout << "Fare Rs " << fixed << setprecision(2) << fare / 100.0
                 << ", balance Rs " << balance / 100.0 << '\n';
        } else {
            cout << "Denied (minimum balance rule), balance Rs "
                 << balance / 100.0 << '\n';
        }
    }
    cout << "Final balance Rs " << fixed << setprecision(2) << balance / 100.0 << '\n';
    return 0;
}
