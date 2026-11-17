#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;
class Time{
 int s;void norm(){s=(s%86400+86400)%86400;}
public:
 Time(int h=0,int m=0,int sec=0):s(h*3600+m*60+sec){norm();}
 Time& operator++(){++s;norm();return *this;}
 Time operator++(int){Time old=*this;++*this;return old;}
 bool operator==(const Time&x)const{return s==x.s;}
 bool operator<(const Time&x)const{return s<x.s;}
 friend ostream& operator<<(ostream&o,const Time&t){int h=t.s/3600,m=t.s/60%60,s=t.s%60;
  return o<<h<<':'<<(m<10?"0":"")<<m<<':'<<(s<10?"0":"")<<s;}
};
class Playlist{
 vector<string> v;
public: Playlist(initializer_list<string>x):v(x){}
 string& operator[](int i){if(i<0||i>=int(v.size()))throw out_of_range("playlist index out of range");return v[i];}
 const string& operator[](int i)const{if(i<0||i>=int(v.size()))throw out_of_range("playlist index out of range");return v[i];}
 int size()const{return int(v.size());}
};
int main(){Time t(0,0,5);Time a=t++;Time b=++t;cout<<a<<' '<<b<<' '<<t<<'\\n';
 Time roll(0,59,59);++roll;cout<<"Rollover "<<roll<<'\\n';
 Playlist p={"Track A","Track B"};cout<<p[0]<<' '<<p[1]<<'\\n';
 try{cout<<p[p.size()];}catch(const out_of_range&e){cout<<e.what()<<'\\n';}}
