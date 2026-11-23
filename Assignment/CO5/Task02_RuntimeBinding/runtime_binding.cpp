#include <iostream>

struct Bill {
    virtual ~Bill() { std::cout << "~Bill "; }
    virtual double total() const = 0;
    void show() const { std::cout << total() << ' '; }
};

struct OPBill : Bill {
    ~OPBill() override { std::cout << "~OPBill "; }
    double total() const override { return 500.0; }
};

int main() {
    Bill* b = new OPBill;
    b->show();
    delete b;
    std::cout << '\n';
    return 0;
}

// Expected output:
// 500 ~OPBill ~Bill
//
// show() is non-virtual, but it calls the virtual total() function.
// The call is dispatched to OPBill::total() using the object's dynamic type.
// The virtual destructor ensures OPBill is destroyed before Bill.
