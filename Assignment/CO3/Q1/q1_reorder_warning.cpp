#include <iostream>
struct Wrong { int first; int second; Wrong():second(20),first(second){} };
int main(){ Wrong w; std::cout<<w.first<<' '<<w.second<<'\\n'; }
