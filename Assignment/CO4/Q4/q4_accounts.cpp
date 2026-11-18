#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Account {
public:
    double rate() const { return 3.5; } // non-virtual: static binding
    virtual double vrate() const { return 3.5; }
    virtual void show() const { cout << "Account destroyed\n"; }
    virtual ~Account() = default;
};
class SeniorAccount : public Account {
    double* history;
public:
    SeniorAccount() : history(new double[100]{}) {}
    double rate() const { return 4.0; }
    double vrate() const override { return 4.0; }
    void show() const override { cout << "SeniorAccount destroyed\n"; }
    ~SeniorAccount() override { delete[] history; }
};

int main() {
    vector<unique_ptr<Account>> accounts;
    accounts.push_back(unique_ptr<Account>(new Account()));
    accounts.push_back(unique_ptr<Account>(new SeniorAccount()));
    for (const auto& a : accounts) cout << a->vrate() << '\n';

    SeniorAccount senior;
    Account* p = &senior;
    Account sliced = senior;
    cout << p->rate() << ' ' << p->vrate() << ' '
         << sliced.vrate() << '\n';
}
