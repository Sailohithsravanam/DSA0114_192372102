#include <chrono>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <variant>
#include <vector>

using Clock = std::chrono::steady_clock;

struct VirtualBill {
    virtual ~VirtualBill() = default;
    virtual double total() const = 0;
};
struct VOut : VirtualBill {
    double a, b;
    VOut(double x, double y) : a(x), b(y) {}
    double total() const override { return a + b; }
};
struct VIn : VirtualBill {
    double days, rate, extra;
    VIn(double d, double r, double e) : days(d), rate(r), extra(e) {}
    double total() const override { return days * rate + extra; }
};

struct Record {
    int kind;
    double x, y, z;
};
double switchTotal(const Record& r) {
    switch (r.kind) {
        case 0: return r.x + r.y;
        case 1: return r.x * r.y + r.z;
        default: return 0.0;
    }
}

struct OutValue {
    double a, b;
    double total() const { return a + b; }
};
struct InValue {
    double days, rate, extra;
    double total() const { return days * rate + extra; }
};
using VariantBill = std::variant<OutValue, InValue>;
double variantTotal(const VariantBill& b) {
    return std::visit([](const auto& value) { return value.total(); }, b);
}

template <typename F>
double measureMs(F function) {
    const auto start = Clock::now();
    volatile double result = function();
    const auto end = Clock::now();
    (void)result;
    return std::chrono::duration<double, std::milli>(end - start).count();
}

void billBench(std::size_t n) {
    std::vector<VirtualBill*> virtualBills;
    std::vector<Record> records;
    std::vector<VariantBill> variants;
    virtualBills.reserve(n);
    records.reserve(n);
    variants.reserve(n);

    for (std::size_t i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            virtualBills.push_back(new VOut(500.0, 1200.0));
            records.push_back({0, 500.0, 1200.0, 0.0});
            variants.push_back(OutValue{500.0, 1200.0});
        } else {
            virtualBills.push_back(new VIn(3.0, 2500.0, 40000.0));
            records.push_back({1, 3.0, 2500.0, 40000.0});
            variants.push_back(InValue{3.0, 2500.0, 40000.0});
        }
    }

    const double tVirtual = measureMs([&]() {
        double sum = 0.0;
        for (const auto* b : virtualBills) sum += b->total();
        return sum;
    });
    const double tSwitch = measureMs([&]() {
        double sum = 0.0;
        for (const auto& r : records) sum += switchTotal(r);
        return sum;
    });
    const double tVariant = measureMs([&]() {
        double sum = 0.0;
        for (const auto& b : variants) sum += variantTotal(b);
        return sum;
    });

    std::cout << n << ',' << tVirtual << ',' << tSwitch << ',' << tVariant << '\n';

    for (auto* b : virtualBills) delete b;
}

bool validReturn(double amount) {
    return amount >= 0.0 && amount <= 1000000.0;
}
bool validThrow(double amount) {
    if (amount < 0.0) throw std::invalid_argument("negative");
    if (amount > 1000000.0) throw std::out_of_range("too large");
    return true;
}

void exceptionBench(std::size_t n, int invalidPercent) {
    std::vector<double> amounts(n, 100.0);
    const std::size_t invalidCount = n * static_cast<std::size_t>(invalidPercent) / 100;
    for (std::size_t i = 0; i < invalidCount; ++i)
        amounts[i] = -1.0;

    const double returnMs = measureMs([&]() {
        std::size_t errors = 0;
        for (double x : amounts) if (!validReturn(x)) ++errors;
        return static_cast<double>(errors);
    });

    const double exceptionMs = measureMs([&]() {
        std::size_t errors = 0;
        for (double x : amounts) {
            try {
                (void)validThrow(x);
            } catch (const std::exception&) {
                ++errors;
            }
        }
        return static_cast<double>(errors);
    });

    std::cout << invalidPercent << "% invalid: return-code="
              << returnMs << " ms, exceptions=" << exceptionMs << " ms\n";
}

int main() {
    std::cout << "Bill benchmark (ms): count,virtual,switch,variant\n";
    for (std::size_t n : {1000u, 1000000u, 10000000u})
        billBench(n);

    std::cout << "\nValidation benchmark (1,000,000 claims):\n";
    const std::size_t n = 1000000;
    exceptionBench(n, 0);
    exceptionBench(n, 1);
    exceptionBench(n, 50);

    std::cout << "\nsizeof(VariantBill): " << sizeof(VariantBill) << " bytes\n";
    return 0;
}

// Run with -O2. This program prints actual timings from the machine on which
// it is executed. Data generation is outside the timed loops. Repeat runs
// and report median/average. Timings are not portable or pre-filled.
