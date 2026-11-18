
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <utility>
using namespace std;

class Vehicle {
protected:
    string regNo;
    double dailyRate;
    bool rented = false;

public:
    Vehicle(string r, double rate)
        : regNo(move(r)), dailyRate(rate) {}

    virtual double charge(int days) const = 0;
    virtual string type() const = 0;

    virtual void details() const {
        cout << type() << " " << regNo
             << " daily=" << dailyRate;
    }

    bool rent() {
        if (rented)
            return false;

        rented = true;
        return true;
    }

    double returnVehicle(int daysLate) {
        if (!rented)
            return 0.0;

        rented = false;
        return charge(1 + (daysLate > 0 ? daysLate : 0));
    }

    virtual ~Vehicle() = default;
};

class Bicycle : public Vehicle {
public:
    Bicycle(string r, double rate)
        : Vehicle(move(r), rate) {}

    double charge(int days) const override {
        return dailyRate * days;
    }

    string type() const override {
        return "Bicycle";
    }
};

class MotorVehicle : public Vehicle {
protected:
    double fuelLevel;
    string serviceDue;

public:
    MotorVehicle(string r, double rate,
                 double fuel, string due)
        : Vehicle(move(r), rate),
          fuelLevel(fuel), serviceDue(move(due)) {}
};

class TwoWheeler : public MotorVehicle {
public:
    TwoWheeler(string r, double rate,
               double fuel, string due)
        : MotorVehicle(move(r), rate, fuel, move(due)) {}

    double charge(int days) const override {
        return dailyRate * days;
    }

    string type() const override {
        return "TwoWheeler";
    }
};

class Car : public MotorVehicle {
protected:
    int seats;

public:
    Car(string r, double rate, double fuel,
        string due, int s)
        : MotorVehicle(move(r), rate, fuel, move(due)),
          seats(s) {}

    double charge(int days) const override {
        return dailyRate * days;
    }

    string type() const override {
        return "Car";
    }
};

class ElectricCar : public Car {
    double batteryKwh;
    double ratePerKwh;

public:
    ElectricCar(string r, double rate, double fuel,
                string due, int s,
                double battery, double kwhRate)
        : Car(move(r), rate, fuel, move(due), s),
          batteryKwh(battery), ratePerKwh(kwhRate) {}

    double charge(int days) const override {
        return dailyRate * days +
               batteryKwh * ratePerKwh;
    }

    string type() const override {
        return "ElectricCar";
    }
};

class ElectricBus : public MotorVehicle {
    int seats;
    double batteryKwh;
    double ratePerKwh;

public:
    ElectricBus(string r, double rate, double fuel,
                string due, int s,
                double battery, double kwhRate)
        : MotorVehicle(move(r), rate, fuel, move(due)),
          seats(s), batteryKwh(battery),
          ratePerKwh(kwhRate) {}

    double charge(int days) const override {
        return dailyRate * days +
               batteryKwh * ratePerKwh;
    }

    string type() const override {
        return "ElectricBus";
    }
};

int main() {
    vector<unique_ptr<Vehicle>> fleet;

    fleet.push_back(unique_ptr<Vehicle>(
        new Bicycle("BI-101", 100)
    ));

    fleet.push_back(unique_ptr<Vehicle>(
        new TwoWheeler("TW-202", 250, 5, "2026-12-01")
    ));

    fleet.push_back(unique_ptr<Vehicle>(
        new Car("CA-303", 1500, 30, "2026-12-10", 5)
    ));

    fleet.push_back(unique_ptr<Vehicle>(
        new ElectricCar("EV-404", 1800, 0,
                        "2026-12-15", 5, 40, 8)
    ));

    fleet.push_back(unique_ptr<Vehicle>(
        new ElectricBus("EB-505", 3500, 0,
                        "2026-12-20", 30, 100, 9)
    ));

    for (auto& v : fleet) {
        v->details();

        if (v->rent())
            cout << " | rented";

        cout << " | return charge="
             << v->returnVehicle(1) << '\n';
    }

    return 0;
}

