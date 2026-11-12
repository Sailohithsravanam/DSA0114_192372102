#include <iostream>
#include <chrono>
using namespace std;
volatile long long sinkValue=0;
int normalSquare(int x) { return x*x; }
inline int inlineSquare(int x) { return x*x; }
int main() {
    constexpr int N=10000000;
    auto start1=chrono::high_resolution_clock::now();
    long long a=0;
    for(int i=0;i<N;++i) a+=normalSquare(i%1000);
    auto end1=chrono::high_resolution_clock::now();
    sinkValue=a;
    auto start2=chrono::high_resolution_clock::now();
    long long b=0;
    for(int i=0;i<N;++i) b+=inlineSquare(i%1000);
    auto end2=chrono::high_resolution_clock::now();
    sinkValue=b;
    cout<<"Normal function: "
        <<chrono::duration<double,milli>(end1-start1).count()<<" ms\n";
    cout<<"Inline function: "
        <<chrono::duration<double,milli>(end2-start2).count()<<" ms\n";
    cout<<"Check sums: "<<a<<' '<<b<<'\n';
}
