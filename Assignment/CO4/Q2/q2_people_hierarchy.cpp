#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int id;
    string phone;
public:
    Person(string n, int i, string p) : name(move(n)), id(i), phone(move(p)) {}
    virtual void display() const {
        cout << name << " ID:" << id << " Phone:" << phone;
    }
    virtual ~Person() = default;
};

class Student : virtual public Person {
protected:
    string programme;
    double cgpa;
public:
    Student(string n, int i, string p, string prog, double g)
        : Person(n, i, p), programme(move(prog)), cgpa(g) {}
    void display() const override {
        Person::display();
        cout << " Programme:" << programme << " CGPA:" << cgpa;
    }
};

class Staff : virtual public Person {
protected:
    string department;
    double salary;
public:
    Staff(string n, int i, string p, string d, double s)
        : Person(n, i, p), department(move(d)), salary(s) {}
    void display() const override {
        Person::display();
        cout << " Department:" << department << " Salary:" << salary;
    }
};

class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(string n, int i, string p, string prog, double g,
                      string dept, double sal)
        : Person(n, i, p), Student(n, i, p, prog, g),
          Staff(n, i, p, dept, sal) {}
    void display() const override {
        Person::display();
        cout << " Programme:" << programme << " CGPA:" << cgpa
             << " Department:" << department << " Salary:" << salary;
    }
};

class ResearchScholar : public Student {
    double fellowship;
public:
    ResearchScholar(string n, int i, string p, string prog, double g, double f)
        : Person(n, i, p), Student(n, i, p, prog, g), fellowship(f) {}
    void display() const override {
        Student::display();
        cout << " Fellowship:" << fellowship;
    }
};

int main() {
    TeachingAssistant ta("Kavya", 1, "9876543210", "CSE", 8.7, "AI", 25000);
    ta.display(); cout << '\n';
    ResearchScholar rs("Arun", 2, "9123456780", "CSE", 9.1, 12000);
    rs.display(); cout << '\n';
}