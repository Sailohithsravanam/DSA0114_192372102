#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Staff {
protected:
    string name;
    int id;
    double basic;
public:
    Staff(string n, int i, double b) : name(move(n)), id(i), basic(b) {}
    virtual double pay() const = 0;
    virtual void print() const {
        cout << name << " (" << id << "): " << pay() << '\n';
    }
    virtual ~Staff() = default;
};

class Professor : public Staff {
    double research;
public:
    Professor(string n, int i, double b, double r)
        : Staff(move(n), i, b), research(r) {}
    double pay() const override { return basic * 1.42 + research; }
};

class LabAssistant : public Staff {
public:
    LabAssistant(string n, int i, double b) : Staff(move(n), i, b) {}
    double pay() const override { return basic * 1.42; }
};

class GuestFaculty : public Staff {
    double hours, ratePerHour;
public:
    GuestFaculty(string n, int i, double h, double r)
        : Staff(move(n), i, 0), hours(h), ratePerHour(r) {}
    double pay() const override { return hours * ratePerHour; }
};

int main() {
    vector<unique_ptr<Staff>> payroll;

    payroll.push_back(unique_ptr<Staff>(
        new Professor("Anita", 101, 50000, 8000)
    ));

    payroll.push_back(unique_ptr<Staff>(
        new LabAssistant("Ravi", 102, 30000)
    ));

    payroll.push_back(unique_ptr<Staff>(
        new GuestFaculty("Meera", 103, 40, 900)
    ));

    for (const auto& person : payroll)
        person->print();

    return 0;
}
