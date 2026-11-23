#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class BillingError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class ClaimError : public BillingError {
public:
    using BillingError::BillingError;
};

class UnknownPackageError : public BillingError {
public:
    using BillingError::BillingError;
};

class Bill {
protected:
    std::string patient_;

    static void checkNonNegative(double value, const std::string& field) {
        if (value < 0.0)
            throw BillingError("negative " + field);
    }

public:
    explicit Bill(const std::string& patient) : patient_(patient) {}
    virtual ~Bill() noexcept = default;

    virtual double total() const = 0;
    virtual std::string type() const = 0;

    void print() const {
        std::cout << type() << ' ' << patient_ << ": " << total() << '\n';
    }
};

class OutPatientBill : public Bill {
    double consultation_, tests_;
public:
    OutPatientBill(const std::string& p, double c, double t)
        : Bill(p), consultation_(c), tests_(t) {
        checkNonNegative(c, "consultation charge");
        checkNonNegative(t, "test charge");
    }
    double total() const override { return consultation_ + tests_; }
    std::string type() const override { return "OP"; }
};

class InPatientBill : public Bill {
    int days_;
    double perDay_, procedures_, medicines_;
public:
    InPatientBill(const std::string& p, int d, double rate,
                  double procedures, double medicines)
        : Bill(p), days_(d), perDay_(rate),
          procedures_(procedures), medicines_(medicines) {
        if (d < 0) throw BillingError("negative number of days");
        checkNonNegative(rate, "room rate");
        checkNonNegative(procedures, "procedure charge");
        checkNonNegative(medicines, "medicine charge");
    }
    double total() const override {
        return days_ * perDay_ + procedures_ + medicines_;
    }
    std::string type() const override { return "IP"; }
};

class DayCareBill : public Bill {
    double packagePrice_;
public:
    DayCareBill(const std::string& p, double price)
        : Bill(p), packagePrice_(price) {
        checkNonNegative(price, "package price");
    }
    double total() const override { return packagePrice_; }
    std::string type() const override { return "DAYCARE"; }
};

class EmergencyBill : public Bill {
    double baseCharge_, ratePerMinute_;
    int minutes_;
public:
    EmergencyBill(const std::string& p, double base, int minutes, double rate)
        : Bill(p), baseCharge_(base), ratePerMinute_(rate), minutes_(minutes) {
        checkNonNegative(base, "emergency base charge");
        checkNonNegative(rate, "emergency minute rate");
        if (minutes < 0) throw BillingError("negative emergency minutes");
    }
    double total() const override {
        return baseCharge_ + minutes_ * ratePerMinute_;
    }
    std::string type() const override { return "EMERGENCY"; }
};

class Payer {
public:
    virtual ~Payer() noexcept = default;
    virtual double amountCovered(const Bill& bill) const = 0;
};

class SelfPay : public Payer {
public:
    double amountCovered(const Bill& bill) const override {
        return bill.total();
    }
};

class Insurance : public Payer {
    double coverLimit_;
    double copayPercent_;
public:
    Insurance(double limit, double copay)
        : coverLimit_(limit), copayPercent_(copay) {
        if (limit < 0.0 || copay < 0.0 || copay > 100.0)
            throw ClaimError("invalid insurance policy");
    }
    double amountCovered(const Bill& bill) const override {
        const double eligible = std::min(bill.total(), coverLimit_);
        return eligible * (1.0 - copayPercent_ / 100.0);
    }
};

class GovernmentScheme : public Payer {
    double packageRate_;
public:
    explicit GovernmentScheme(double rate) : packageRate_(rate) {
        if (rate < 0.0) throw ClaimError("negative scheme package rate");
    }
    double amountCovered(const Bill& bill) const override {
        if (bill.type() != "DAYCARE")
            throw UnknownPackageError("no government package for this bill type");
        return std::min(bill.total(), packageRate_);
    }
};

int main() {
    try {
        std::vector<std::unique_ptr<Bill>> bills;
        bills.push_back(std::unique_ptr<Bill>(
            new OutPatientBill("Ravi", 500, 1200)));
        bills.push_back(std::unique_ptr<Bill>(
            new InPatientBill("Meena", 3, 2500, 30000, 10000)));
        bills.push_back(std::unique_ptr<Bill>(
            new DayCareBill("Arun", 18000)));
        bills.push_back(std::unique_ptr<Bill>(
            new EmergencyBill("Sara", 1000, 30, 50)));

        double dailyTotal = 0.0;
        for (const auto& bill : bills) {
            bill->print();
            dailyTotal += bill->total();
        }
        std::cout << "Daily total: " << dailyTotal << '\n';

        SelfPay self;
        Insurance insurance(50000, 10);
        GovernmentScheme scheme(15000);

        std::cout << "Ravi self-pay covered: "
                  << self.amountCovered(*bills[0]) << '\n';
        std::cout << "Meena insurance covered: "
                  << insurance.amountCovered(*bills[1]) << '\n';
        std::cout << "Arun government covered: "
                  << scheme.amountCovered(*bills[2]) << '\n';

        try {
            (void)scheme.amountCovered(*bills[0]);
        } catch (const UnknownPackageError& e) {
            std::cout << "Package error: " << e.what() << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << "Billing error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
