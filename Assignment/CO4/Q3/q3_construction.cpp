
#include <iostream>
#include <string>
using namespace std;
class Address {
    string city;
    int pin;

public:
    Address(string c, int p) : city(c), pin(p) {
        cout << "Address constructed\n";
    }

    ~Address() {
        cout << "Address destroyed\n";
    }
};
class Course {
    string courseName;

public:
    Course(string c) : courseName(c) {
        cout << "Course constructed\n";
    }

    ~Course() {
        cout << "Course destroyed\n";
    }
};
class Person {
protected:
    string name;
    int age;
    Address address;

public:
    Person(string n, int a, string city, int pin)
        : name(n), age(a), address(city, pin) {
        cout << "Person constructed\n";
    }

    virtual ~Person() {
        cout << "Person destroyed\n";
    }
};
class Student : virtual public Person {
protected:
    long long regNo;
    Course course;

public:
    Student(string n, int a, long long r,
            string city, int pin, string courseName)
        : Person(n, a, city, pin),
          regNo(r), course(courseName) {
        cout << "Student constructed\n";
    }

    ~Student() override {
        cout << "Student destroyed\n";
    }
};
class Staff : virtual public Person {
protected:
    string department;

public:
    Staff(string n, int a, string city,
          int pin, string dept)
        : Person(n, a, city, pin),
          department(dept) {
        cout << "Staff constructed\n";
    }

    ~Staff() override {
        cout << "Staff destroyed\n";
    }
};
class TeachingAssistant : public Student, public Staff {
public:
    TeachingAssistant(string n, int a, long long r,
                      string city, int pin,
                      string courseName, string dept)
        : Person(n, a, city, pin),
          Student(n, a, r, city, pin, courseName),
          Staff(n, a, city, pin, dept) {
        cout << "TeachingAssistant constructed\n";
    }

    ~TeachingAssistant() override {
        cout << "TeachingAssistant destroyed\n";
    }
};

int main() {

    cout << "\n-- Student --\n";
    {
        Student s("Kavya", 19, 192311001,
                  "Salem", 636001, "C++");
    }

    cout << "\n-- Staff --\n";
    {
        Staff st("Ravi", 40, "Chennai",
                 600001, "CSE");
    }

    cout << "\n-- Teaching Assistant --\n";
    {
        TeachingAssistant ta("Maya", 22, 192311002,
                             "Salem", 636001, "C++", "CSE");
    }

    return 0;
}

