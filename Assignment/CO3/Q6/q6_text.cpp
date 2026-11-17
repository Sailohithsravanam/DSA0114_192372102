#include <iostream>
#include <cstring>
using namespace std;
class Text{
 char* p;
public:
 Text(const char*s=""){size_t n=strlen(s);p=new char[n+1];memcpy(p,s,n+1);}
 Text(const Text&o){size_t n=strlen(o.p);p=new char[n+1];memcpy(p,o.p,n+1);cout<<"[copy] ";}
 Text&operator=(const Text&o){if(this!=&o){size_t n=strlen(o.p);char*q=new char[n+1];memcpy(q,o.p,n+1);delete[]p;p=q;}return *this;}
 ~Text(){delete[]p;}
 Text&operator+=(const Text&o){size_t a=strlen(p),b=strlen(o.p);char*q=new char[a+b+1];memcpy(q,p,a);memcpy(q+a,o.p,b+1);delete[]p;p=q;return *this;}
 friend Text operator+(const Text&a,const Text&b){Text t(a);t+=b;return t;}
 bool operator==(const Text&o)const{return strcmp(p,o.p)==0;}
 bool operator!=(const Text&o)const{return !(*this==o);}
 friend ostream&operator<<(ostream&o,const Text&t){return o<<t.p;}
};
int main(){Text a("Hello"),b(" World"),empty("");Text c=a+b;cout<<"Result: "<<c<<'\\n';
 cout<<boolalpha<<(a==Text("Hello"))<<' '<<(a!=b)<<'\\n';empty=empty;cout<<"Empty: ["<<empty<<"]\\n";}
