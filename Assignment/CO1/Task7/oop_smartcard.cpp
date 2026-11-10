#include <iostream>
using namespace std;

class SmartCard {
private:
    int balancePaise;
    const int minimumBalance = 5000;
public:
    SmartCard(int initialBalance) : balancePaise(initialBalance) {}

    bool canTravel(int farePaise) const {
        return farePaise >= 0 && balancePaise - farePaise >= minimumBalance;
    }

    void deductFare(int farePaise) {
        if (canTravel(farePaise)) {
            balancePaise -= farePaise;
            cout << "Journey approved. Balance: Rs " << balancePaise / 100.0 << '\n';
        } else {
            cout << "Journey denied. Balance: Rs " << balancePaise / 100.0 << '\n';
        }
    }
};

int main() {
    SmartCard card(10000);
    card.deductFare(2000);
    card.deductFare(4000);
    return 0;
}
