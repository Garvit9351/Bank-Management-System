#include<iostream>
#include<iomanip>
#include<fstream>
#include<cctype>
#include <string>
#include <cstring>
using namespace std;
string adminPassword="Golu@2003";
class Bank_Account{
	int account_number;
	char name[50];
	char type;
	int money_Deposit;
	int pin;
public:
	int retacno() const{
		return account_number;
	}
	void report() const;
	void dep(int x){
		money_Deposit+=x;
	}
	void draw(int x){
		money_Deposit-=x;
	}
	int retdeposit() const{
		cout<<money_Deposit;
		
	}
	int getAccNo() const;
	
void create_Account();
void Display_Account();
 bool checkPIN(int enteredPIN) const;
 bool isAdmin ();

	 
};
void write_account();
void delete_account(int);
void display_details(int);
void Money_deposit_withdraw(int, int);
void display_all();
bool Bank_Account::checkPIN(int enteredPIN) const {
    return (pin == enteredPIN);
}
int Bank_Account::getAccNo() const
{
	return account_number;
}
void Bank_Account::report() const
{
    cout << setw(12) << left << account_number
         << setw(20) << left << name
         << setw(6) << left << type
         << setw(10) << right << money_Deposit
         << endl;
}
bool Bank_Account::isAdmin(){
	string password;
	cout << "Enter the admin password: ";
	cin >> password;
	return (password == adminPassword);
}
void Bank_Account::create_Account(){
	//System("CLS");
	cout<<"\t Enter the account number ";
	cin>>account_number;
	cout<<"enter the name of account holder ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\t enter the type of account (c/s):";
	cin>>type;
	type=toupper(type);
	cout<<"\t enter the initial amount";
	cin>>money_Deposit;
	bool validPIN = false;
    do {
        cout << "Enter the PIN for the account: ";
        cin >> pin;
        int reenteredPIN;
        cout << "Reenter the PIN for verification: ";
        cin >> reenteredPIN;
        if (pin == reenteredPIN) {
            validPIN = true;
            cout << "Account is created." << endl;
        }
        else {
            cout << "The entered PINs do not match. Please try again." << endl;
        }
    } while (!validPIN);
}
void Bank_Account::Display_Account(){
	cout<<"account number "<<account_number;
	cout<<"holder name"<<name;
	cout<<"type of account"<<type;
	cout<<"balance amount"<<money_Deposit;
}
int main(){
	int ch,num;
	do{
     system("CLS");
	cout<<"\t\tBANK MANAGEMENT SYSTEM\n";
	cout<<"\t\t ::MAIN MENU::\n";
	cout<<"1 create account  ";
	cout<<"\n 2 deposite money ";
	cout<<"\n 3 with draw money";
	cout<<"\n 4 balance enqiry";
	cout<<"\n 5 all account holder list";
	cout<<"\n 6 close an account";
	cout<<"\n 7 exit \n";
	cout<<"enter a choice (1-7)\n";
	cin>>ch;
	switch(ch)
		{
		case 1:
			write_account();
			break;
		case 2:
			system("CLS");
			cout<<"\n\n\tPlease Enter The Bank_Account No. : ";
			cin>>num;
			Money_deposit_withdraw(num, 1);
			break;
		case 3:
			system("CLS");
			cout<<"\n\n\tPlease Enter The Bank_Account No. : "; cin>>num;
			Money_deposit_withdraw(num, 2);
			break;
		case 4:
			system("CLS");
			cout<<"\n\n\tPlease Enter The Bank_Account No. : "; cin>>num;
			display_details(num);
			break;
		case 5:
			display_all();
			break;
		case 6:
			system("CLS");
			cout<<"\n\n\tPlease Enter The Bank_Account No. : "; cin>>num;
			delete_account(num);
			break;
		 case 7:
		 	system("CLS");
			cout<<"\n\n\tBrought To You By code-projects.org";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!='7');
	return 0;
}
void write_account(){//function to write record in binary file;
Bank_Account ac;
ofstream outFile;
outFile.open("account.data",ios::binary|ios::app);
ac.create_Account();
outFile.write(reinterpret_cast<char * >(&ac),sizeof(Bank_Account));
outFile.close();
}
void delete_account(int n){
	Bank_Account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile){
		cout<<"\n File could not be open || press any ";
		return;
	}
	
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *>(&ac),sizeof(Bank_Account))){
		if(ac.retacno()!=n){
			outFile.write(reinterpret_cast<char *>(&ac),sizeof(Bank_Account));       
		}
	}
	inFile.close();
	outFile.close();
	remove("Bank_account.dat");
	rename("Temp.dat","Bank_account.dat");
	cout<<"record is deleted";
}
void display_details(int n){
	Bank_Account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile){
		cout<<"File could not be open||press any key...";
		return;
	}
	cout<<"\t Bank Account details "<<endl;
	while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(Bank_Account))) {
        if (ac.retacno() == n) {
            int enteredPIN;
            cout << "Enter PIN for the account: ";
            cin >> enteredPIN;
            if (ac.checkPIN(enteredPIN)) {
                ac.Display_Account();
                flag = true;
            }
            else {
                cout << "Invalid PIN. Access denied!" << endl;
            }
        }
    }
    inFile.close();
	if(flag==false)
		cout<<"\n\n\tBank_Account number does not exist";
}
void display_all(){
	system("cls");
	Bank_Account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary|ios::app);
	if(!inFile){
		cout<<"press any key ";
		return;
	}
	if(ac.isAdmin()){	
	cout<<"\n\n\t\tBank_Account HOLDER LIST\n\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account)))
	{
	if (ac.getAccNo() != -953275650) // Check if the account number is not equal to the garbage value
		{
			ac.report();
		}
	}

}
else{
	cout<<"Access denied! Invalid admin password."<<endl;
}
	inFile.close();
	
	
}
void Money_deposit_withdraw(int n,int option ){
	int amt;
	bool found=false;
	int enteredPIN;
	Bank_Account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File){
		cout<<"File could not be open|| Press any key...";
		return;
	}
	while(!File.eof()&&found==false){
		File.read(reinterpret_cast<char *>(&ac),sizeof(Bank_Account));
		if(ac.retacno()==n){
			ac.Display_Account();
			cout << "Enter PIN for the account: ";
			cin >> enteredPIN;
			if (ac.checkPIN(enteredPIN)) {
			if(option==1){
				cout<<"\t enter the amount to be deposited ";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2){
				cout<<"\t enter the amount to be withdraw : ";
				cin>>amt;
				int balance=ac.retdeposit()-amt;
				if(balance<0){
					cout<<"\t Insufficient balance "<<endl;
				}
				else{
					ac.draw(amt);
				}
			} 
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
			cout<<"\n\n\tRecord Updated";
			found=true; 
		}
		else {
				cout << "Invalid PIN. Access denied!" << endl;
				return;
			}
	}
		
	}
	File.close();
	if(found==false){
		cout<<"record is not found";
	}
	 
	
}



