#include <iostream>
#include <string>
using namespace std;
class Event {
 int rows,cols; bool** seats; string name;
public:
 Event(string n,int r,int c):rows(r>0?r:0),cols(c>0?c:0),seats(nullptr),name(n){
  if(rows){seats=new bool*[rows]{}; int i=0; try{for(;i<rows;++i)seats[i]=new bool[cols]{};}
   catch(...){while(i)delete[] seats[--i];delete[] seats;throw;}}
  cout<<"Construct "<<name<<'\\n';
 }
 bool book(int r,int c){if(r<0||r>=rows||c<0||c>=cols||seats[r][c])return false;seats[r][c]=true;return true;}
 bool cancel(int r,int c){if(r<0||r>=rows||c<0||c>=cols||!seats[r][c])return false;seats[r][c]=false;return true;}
 ~Event(){int used=0;for(int i=0;i<rows;++i){for(int j=0;j<cols;++j)used+=seats[i][j];delete[] seats[i];}delete[] seats;
  cout<<"Destroy "<<name<<", booked="<<used<<'\\n';}
};
int main(){Event local("local",2,3);local.book(0,0);{Event block("block",1,2);block.book(0,1);}
 Event* heap=new Event("heap",2,2);heap->book(1,1);delete heap;Event zero("zero",0,4);}
