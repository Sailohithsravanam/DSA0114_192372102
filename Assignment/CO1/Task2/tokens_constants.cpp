#include<iostream>
using namespace std;

#define METRO_NAME "Namma Metro"
const int BASE_FARE = 10;
constexpr int PEAK_START = 8;
enum class Zone { Inner, Middle, Outer };

int main() {
    int passengerCount = 2;
    double sampleFare = 20.50;
    char category = 'S';
    bool isValid = true;
    Zone selectedZone = Zone::Inner;

    cout << "Metro: " << METRO_NAME << '\n';
    cout << "Base fare: Rs " << BASE_FARE << '\n';
    cout << "Peak starts at: " << PEAK_START << ":00\n";
    cout << "Passenger count: " << passengerCount << '\n';
    cout << "Sample fare: " << sampleFare << '\n';
    cout << "Category: " << category << '\n';
    cout << boolalpha << "Valid card: " << isValid << '\n';
    cout << "Zone enum value: " << static_cast<int>(selectedZone) << '\n';
    return 0;
}
