#include <iostream>
using namespace std;

// Redesigned version: circular indexing overwrites the oldest entry in O(1).
class CircularHistory {
    static const int CAP=10;
    int data[CAP];
    int count=0;
    int next=0;
public:
    void add(int value) {
        data[next]=value;
        next=(next+1)%CAP;
        if(count<CAP) ++count;
    }
    void print() const {
        int start=(count==CAP)?next:0;
        for(int i=0;i<count;++i) cout<<data[(start+i)%CAP]<<' ';
        cout<<'\n';
    }
};
int main() {
    CircularHistory h;
    for(int i=1;i<=15;++i) h.add(i);
    cout<<"Last 10 values using circular buffer: ";
    h.print();
}
