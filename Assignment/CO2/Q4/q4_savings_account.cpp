#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class SavingsAccount {
    string accountNumber;
    long long balance;             // stored in paise
    long long transactions[10];    // positive=deposit, negative=withdrawal
    int count, next;
    void addTransaction(long long amount) { // circular insertion
        transactions[next]=amount;
        next=(next+1)%10;
        if(count<10) ++count;
    }
public:
    SavingsAccount(const string& number,long long openingBalance)
        : accountNumber(number),balance(openingBalance),count(0),next(0) {}
    void deposit(long long amount); // defined outside
    bool withdraw(long long amount);
    void miniStatement() const;
    long long getBalance() const { return balance; } // defined inside
};
void SavingsAccount::deposit(long long amount) {
    if(amount<=0) { cout<<"Deposit rejected\n"; return; }
    balance+=amount; addTransaction(amount);
}
bool SavingsAccount::withdraw(long long amount) {
    if(amount<=0 || amount>balance) { cout<<"Withdrawal rejected\n"; return false; }
    balance-=amount; addTransaction(-amount); return true;
}
void SavingsAccount::miniStatement() const {
    cout<<"Account: "<<accountNumber<<"\nLast transactions (oldest to newest):\n";
    int start=(count==10)?next:0;
    for(int i=0;i<count;++i) {
        long long v=transactions[(start+i)%10];
        cout<<(v>=0?"Deposit ":"Withdrawal ")
            <<fixed<<setprecision(2)<<static_cast<double>(v>=0?v:-v)/100.0<<'\n';
    }
    cout<<"Balance: Rs "<<fixed<<setprecision(2)
        <<static_cast<double>(balance)/100.0<<'\n';
}
int main() {
    SavingsAccount account("SB1001",100000);
    account.deposit(5000);
    account.withdraw(12000);
    for(int i=1;i<=10;++i) account.deposit(i*100);
    account.miniStatement();
}
