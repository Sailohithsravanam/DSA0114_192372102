#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;
class Complex{
 double re,im;
public:
 Complex():re(0),im(0){} Complex(double r):re(r),im(0){} Complex(double r,double i):re(r),im(i){}
 double magnitude()const{return hypot(re,im);}
 Complex operator+(const Complex&z)const{return {re+z.re,im+z.im};}
 Complex operator-(const Complex&z)const{return {re-z.re,im-z.im};}
 Complex operator*(const Complex&z)const{return {re*z.re-im*z.im,re*z.im+im*z.re};}
 Complex operator/(const Complex&z)const{double d=z.re*z.re+z.im*z.im;if(d<1e-24)throw domain_error("division by zero impedance");
  return {(re*z.re+im*z.im)/d,(im*z.re-re*z.im)/d};}
 bool operator==(const Complex&z)const{return fabs(re-z.re)<1e-9&&fabs(im-z.im)<1e-9;}
 friend ostream&operator<<(ostream&o,const Complex&z){return o<<z.re<<(z.im<0?" - j":" + j")<<fabs(z.im);}
};
int main(){Complex R(10,0),L(0,8),C(0,-3);Complex series=R+L+C;
 cout<<"Series: "<<series<<", magnitude="<<series.magnitude()<<'\\n';
 Complex z1(10),z2(0,5),parallel=(z1*z2)/(z1+z2);
 cout<<"Parallel: "<<parallel<<", magnitude="<<parallel.magnitude()<<'\\n';
 try{cout<<(z1/Complex(0,0));}catch(const domain_error&e){cout<<"Safe error: "<<e.what()<<'\\n';}}
