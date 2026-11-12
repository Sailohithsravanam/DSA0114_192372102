#include <iostream>
#include <cstdlib>
using namespace std;
class Time {
    int h,m;
public:
    Time(int hh,int mm):h(hh),m(mm) {}
    friend int minutesBetween(const Time& a,const Time& b);
    friend bool earlier(const Time& a,const Time& b);
};
inline int minutesBetween(const Time& a,const Time& b) {
    int x=a.h*60+a.m, y=b.h*60+b.m;
    return abs(x-y); // TODO 1 completed
}
inline bool earlier(const Time& a,const Time& b) {
    return a.h*60+a.m < b.h*60+b.m; // TODO 2 completed
}
int main() {
    Time departure(9,45),arrival(13,10);
    cout<<minutesBetween(departure,arrival)<<' '
        <<boolalpha<<earlier(arrival,departure)<<'\n';
    Time beforeNoon(11,50),afterNoon(12,10),same(12,10);
    cout<<minutesBetween(beforeNoon,afterNoon)<<' '
        <<earlier(beforeNoon,afterNoon)<<'\n';
    cout<<minutesBetween(same,same)<<' '
        <<earlier(same,same)<<'\n';
}
