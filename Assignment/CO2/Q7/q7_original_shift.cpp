#include <iostream>
#include <vector>
using namespace std;

// Original design: remove oldest item by shifting all remaining elements.
class ShiftHistory {
    static const int CAP=10;
    int data[CAP];
    int count=0;
public:
    void add(int value) {
        if(count<CAP) data[count++]=value;
        else {
            for(int i=1;i<CAP;++i) data[i-1]=data[i];
            data[CAP-1]=value;
        }
    }
    void print() const {
        for(int i=0;i<count;++i) cout<<data[i]<<' ';
        cout<<'\n';
    }
};
int main() {
    ShiftHistory h;
    for(int i=1;i<=15;++i) h.add(i);
    cout<<"Last 10 values using shifting: ";
    h.print();
}
