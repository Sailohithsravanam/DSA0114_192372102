#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

int main() {
    int hour;
    cout << "Enter journey hour (0-23): ";
    if (!(cin >> hour) || hour < 0 || hour > 23) {
        cout << "Invalid hour input\n";
        return 1;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string passengerName;
    cout << "Enter passenger name: ";
    getline(cin, passengerName);

    double fare = 20.0;
    cout << fixed << setprecision(2);
    cout << "Passenger: " << passengerName << '\n';
    cout << "Journey hour: " << hour << '\n';
    cout << "Fare: Rs " << fare << '\n';
    return 0;
}
