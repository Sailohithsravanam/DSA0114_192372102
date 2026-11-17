#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
class Money{
 long long paise;
 static Money fromPaise(long long p){Money m;m.paise=p;return m;}
public:
 Money(long long r=0,int p=0):paise(r*100+p){}
 Money operator+(const Money&x)const{return fromPaise(paise+x.paise);}
 Money operator-(const Money&x)const{return fromPaise(paise-x.paise);}
 Money& operator+=(const Money&x){paise+=x.paise;return *this;}
 bool operator==(const Money&x)const{return paise==x.paise;}
 bool operator<(const Money&x)const{return paise<x.paise;}
 friend ostream& operator<<(ostream&o,const Money&m){long long v=llabs(m.paise);if(m.paise<0)o<<'-';
  return o<<"Rs "<<v/100<<'.'<<setw(2)<<setfill('0')<<v%100<<setfill(' ');}
 friend istream& operator>>(istream&i,Money&m){long long r;int p;if(i>>r>>p)m.paise=r*100+p;return i;}
};
int main(){Money a(120,75),b(79,25),c=a+b;cout<<c<<'\\n'<<boolalpha<<(c==Money(200))<<'\\n';
 cout<<"Carry: "<<Money(0,75)+Money(0,50)<<'\\n';cout<<"Negative: "<<Money(1)-Money(2)<<'\\n';c+=Money(1,50);cout<<c<<'\\n';}
