#include <iostream>
#include <iomanip>
using namespace std;

struct Parcel { double kg; bool express; bool insured; };

double charge(double kg, bool express=false, bool insured=false) {
    double total=kg*40.0;
    if(express) total+=30.0;
    if(insured) total+=20.0;
    return total;
}
double charge(int grams) { return (grams/1000.0)*40.0; }
double charge(float kg) { return static_cast<double>(kg)*40.0; }
double charge(const Parcel& p) { return charge(p.kg,p.express,p.insured); }

int main() {
    Parcel parcel{2.5,true,true};
    cout << fixed << setprecision(2);
    cout << "charge(2): " << charge(2) << " [int grams]\n";
    cout << "charge(2.0): " << charge(2.0) << " [double kg]\n";
    cout << "charge(2.0f): " << charge(2.0f) << " [float kg]\n";
    cout << "charge(2.0, true): " << charge(2.0,true) << '\n';
    cout << "charge(2.0, true, true): " << charge(2.0,true,true) << '\n';
    cout << "charge(parcel): " << charge(parcel) << '\n';
}
