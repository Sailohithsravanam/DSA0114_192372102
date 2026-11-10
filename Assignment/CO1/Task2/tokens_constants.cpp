#include <iostream>
#include <string>
using namespace std;

// Macro constant
#define SERVICE_NAME "Metro Smart Card System"

// Compile-time constants
constexpr int BASE_FARE_PAISE = 5000;
constexpr int PEAK_SURCHARGE_PERCENT = 20;

// Enumeration
enum class Zone {
    Inner,
    Middle,
    Outer
};

int main() {

    // 1. Keywords
    // int, const, constexpr, enum, if, return

    // 2. Identifiers
    int passengerId = 101;
    string passengerName = "Sravanam";

    // 3. Constants and literals
    const int MINIMUM_BALANCE_PAISE = 5000;
    constexpr int MAX_FARE_PAISE = 10000;

    // 4. Operators
    int finalFare = BASE_FARE_PAISE +
        (BASE_FARE_PAISE * PEAK_SURCHARGE_PERCENT / 100);

    // 5. Enum class
    Zone passengerZone = Zone::Inner;

    cout << "Metro Smart Card System" << endl;
    cout << "Service: " << SERVICE_NAME << endl;

    cout << "\nPassenger Details" << endl;
    cout << "Passenger ID: " << passengerId << endl;
    cout << "Passenger Name: " << passengerName << endl;

    cout << "\nFare Details" << endl;
    cout << "Base Fare: " << BASE_FARE_PAISE << " paise" << endl;
    cout << "Peak Surcharge: "
         << PEAK_SURCHARGE_PERCENT << "%" << endl;
    cout << "Final Fare: " << finalFare << " paise" << endl;

    cout << "Minimum Balance: "
         << MINIMUM_BALANCE_PAISE << " paise" << endl;

    cout << "Maximum Fare: " << MAX_FARE_PAISE << " paise" << endl;

    if (passengerZone == Zone::Inner) {
        cout << "Passenger Zone: Inner" << endl;
    }

    return 0;
}
