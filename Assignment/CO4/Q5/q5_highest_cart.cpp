#include <iostream>
#include <iomanip>
using namespace std;

class Cart {
    double amount;
public:
    explicit Cart(double a) : amount(a) {}
    double total() const { return amount; }
};

int main() {
    Cart a(120), b(250), c(180);
    Cart* carts[] = {&a, &b, &c};
    Cart* highest = carts[0];
    for (Cart** it = carts; it != carts + 3; ++it)
        if ((*it)->total() > highest->total()) highest = *it;
    cout << fixed << setprecision(2) << highest->total() << '\n';
}