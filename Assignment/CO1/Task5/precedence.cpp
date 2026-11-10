#include <iostream>
using namespace std;
int main() {
    int baseFare = 20;
    bool peak = true;
    bool concession = false;
    int fare = peak ? baseFare * 120 / 100 : baseFare;
    fare = concession ? fare / 2 : fare;
    int x = 5;
    cout << "Fare: Rs " << fare << '\n';
    cout << "x++ returns: " << x++ << '\n';
    cout << "After x++: " << x << '\n';
    cout << "++x returns: " << ++x << '\n';
    cout << "2 + 3 * 4 = " << 2 + 3 * 4 << '\n';
    cout << "-7 / 3 = " << -7 / 3 << '\n';
    cout << "-7 % 3 = " << -7 % 3 << '\n';
    cout << "Use parentheses for readable fare expressions.\n";
    return 0;
}
