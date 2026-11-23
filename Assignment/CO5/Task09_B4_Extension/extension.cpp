#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class Bill {
protected:
    std::string patient_;
public:
    explicit Bill(std::string patient) : patient_(std::move(patient)) {}
    virtual ~Bill() noexcept = default;
    virtual double total() const = 0;
    virtual std::string type() const = 0;
};

class OutPatientBill : public Bill {
    double consultation_, tests_;
public:
    OutPatientBill(const std::string& p, double c, double t)
        : Bill(p), consultation_(c), tests_(t) {}
    double total() const override { return consultation_ + tests_; }
    std::string type() const override { return "OP"; }
};

class TelemedicineBill : public Bill {
    double consultationFee_, platformFee_;
public:
    TelemedicineBill(const std::string& p, double consultation, double platform)
        : Bill(p), consultationFee_(consultation), platformFee_(platform) {
        if (consultation < 0.0 || platform < 0.0)
            throw std::invalid_argument("negative telemedicine fee");
    }
    double total() const override { return consultationFee_ + platformFee_; }
    std::string type() const override { return "TELEMEDICINE"; }
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

class CorporatePayer : public Payer {
    double coveragePercent_;
public:
    explicit CorporatePayer(double percent) : coveragePercent_(percent) {
        if (percent < 0.0 || percent > 100.0)
            throw std::invalid_argument("invalid corporate coverage percentage");
    }
    double amountCovered(const Bill& bill) const override {
        return bill.total() * coveragePercent_ / 100.0;
    }
};

int main() {
    try {
        std::vector<std::unique_ptr<Bill>> bills;
        bills.push_back(std::unique_ptr<Bill>(
            new OutPatientBill("Ravi", 500.0, 1200.0)));
        bills.push_back(std::unique_ptr<Bill>(
            new TelemedicineBill("Anu", 800.0, 100.0)));

        SelfPay self;
        CorporatePayer corporate(80.0);

        for (const auto& bill : bills) {
            std::cout << bill->type() << ' ' << bill->total()
                      << " | self-pay " << self.amountCovered(*bill)
                      << " | corporate " << corporate.amountCovered(*bill)
                      << '\n';
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}

// Extension demonstration:
// TelemedicineBill and CorporatePayer are added as new derived classes.
// The existing OutPatientBill, SelfPay and Bill/Payer interfaces are unchanged.
