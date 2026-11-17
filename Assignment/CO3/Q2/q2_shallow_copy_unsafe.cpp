// Intentionally unsafe demonstration. DO NOT RUN: double delete / undefined behaviour.
#include <string>
class Prescription { int n; std::string* medicines;
public: explicit Prescription(int x):n(x),medicines(new std::string[x]){}
 ~Prescription(){delete[] medicines;} // no copy constructor: generated copy is shallow
};
int main(){Prescription p(2); Prescription q=p;}
