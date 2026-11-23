#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class ClaimError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

double approve(double billed, double cover) {
    if (billed < 0.0 || cover < 0.0)
        throw std::invalid_argument("negative amount");
    if (billed > cover)
        throw ClaimError("exceeds cover");
    return billed;
}

double settle(double billed, double cover) {
    try {
        return approve(billed, cover);
    } catch (const ClaimError& e) {
        std::cout << "audit: " << e.what() << '\n';
        throw; // rethrow the same exception object
    }
}

void validate(double amount) {
    if (amount < 0.0)
        throw std::invalid_argument("negative");
    if (amount > 1e6)
        throw std::out_of_range("too large");
    std::cout << "ok ";
}

void process(double amount) {
    try {
        validate(amount);
    } catch (const std::out_of_range& e) {
        std::cout << "[log " << e.what() << "] ";
        throw;
    }
}

int main() {
    std::cout << "Claim settlement tests:\n";
    double cases[][2] = {{40000, 50000}, {60000, 50000}, {-1, 50000}};
    for (auto& c : cases) {
        try {
            double paid = settle(c[0], c[1]);
            std::cout << "approved " << paid << '\n';
        } catch (const ClaimError& e) {
            std::cout << "claim rejected: " << e.what() << '\n';
        } catch (const std::exception& e) {
            std::cout << "error: " << e.what() << '\n';
        }
    }

    std::cout << "\nValidation and rethrow tests:\n";
    for (double amount : {100.0, -5.0, 2e6}) {
        try {
            process(amount);
            std::cout << "done ";
        } catch (const std::exception& e) {
            std::cout << "caught " << e.what() << ' ';
        }
    }
    std::cout << '\n';

    // Other test cases to try:
    // std::stod("abc") throws std::invalid_argument.
    // std::vector<int> huge; huge.resize(SIZE_MAX); may throw std::bad_alloc
    // or fail due to operating-system memory overcommit. Test separately.
    try {
        const double parsed = std::stod("123.5");
        std::cout << "Parsed number: " << parsed << '\n';
    } catch (const std::exception& e) {
        std::cout << "Conversion error: " << e.what() << '\n';
    }
    try {
        (void)std::stod("abc");
    } catch (const std::invalid_argument& e) {
        std::cout << "Text conversion error: " << e.what() << '\n';
    }

    return 0;
}

// Claim settlement expected:
// approved 40000
// audit: exceeds cover
// claim rejected: exceeds cover
// error: negative amount
//
// Validation expected:
// ok done caught negative [log too large] caught too large
