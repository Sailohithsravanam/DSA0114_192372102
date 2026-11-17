#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
class Book {
 string title, author; int copies;
public:
 Book():Book("Untitled","Unknown",0){}
 explicit Book(const string& t):Book(t,"Unknown",1){}
 Book(const string& t,int c):Book(t,"Unknown",c){}
 Book(const string& t,const string& a,int c):title(t),author(a),copies(c) {
  if(c<0) throw invalid_argument("Copies cannot be negative");
 }
 void print() const { cout<<title<<" | "<<author<<" | copies="<<copies<<'\\n'; }
};
int main(){
 Book a; Book b("Donated title"); Book c("C++",4); Book d("OOP","Author",3);
 a.print(); b.print(); c.print(); d.print();
 try { Book bad("Bad","Author",-1); bad.print(); }
 catch(const exception& e){ cout<<"Rejected: "<<e.what()<<'\\n'; }
 // explicitBook = "Dune"; // intentionally fails: explicit constructor
}
