#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

int main() {
    const long long farePaise = 2000; // Rs 20.00
    const long long counts[] = {20000, 500000, 3000000};

    cout << fixed << setprecision(2);
    for (long long n : counts) {
        long long integerTotalPaise = n * farePaise;
        double doubleTotalRupees = n * 20.00;
        cout << "Journeys: " << n << '\n';
        cout << "Integer paise total: Rs " << integerTotalPaise / 100.0 << '\n';
        cout << "Double total: Rs " << doubleTotalRupees << '\n';
    }
    cout << "Use long long for large integer-paise totals.\n";
    return 0;
}
