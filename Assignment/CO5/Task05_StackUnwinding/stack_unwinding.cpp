#include <iostream>
#include <string>

struct Guard {
    std::string name;
    explicit Guard(const std::string& s) : name(s) {}
    ~Guard() { std::cout << '~' << name << ' '; }
};

void f() {
    Guard g("f");
    throw 42;
}

int main() {
    try {
        Guard m("main");
        f();
        std::cout << "not printed ";
    } catch (int x) {
        std::cout << "caught " << x;
    } catch (...) {
        std::cout << "other";
    }
    std::cout << '\n';
    return 0;
}

// Expected output:
// ~f caught 42 ~main
//
// g is destroyed while the exception leaves f().
// m is destroyed when the try block's scope is exited.
// "not printed" is skipped because throw transfers control to a handler.
