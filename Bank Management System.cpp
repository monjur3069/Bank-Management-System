#include<bits/stdc++.h>
using namespace std;

class Bank_Account{
public:
    Account();
    void create_account();
    void account_info() const;
    void withdraw(int);
    void deposite(int);
    void modify();
    void allInfo() const;
    int getBalance() const;
    int getAccountNumber() const;
    char getAccountType() const;

private:
    int accountNumber;
    char accountName[80];
    char accountType;
    int balance;
};


Bank_Account::Account()
{}
void Bank_Account::create_account()
{
    cout<<"Enter Account Number: "<<endl;
    cin>>accountNumber;
    cout<<"Enter Account Name: "<<endl;
    cin.ignore();
	cin.getline(accountName,80);
    cout<<"Enter Accout Type (S/O): Saving = S | Other = O "<<endl;
    cin>>accountType;
    accountType=toupper(accountType);
    cout<<"Enter Initial Balance: "<<endl;
    cout<<"For Saving initial Balance = 500+ | Other = 1000+ : "<<endl;
    cin>>balance;
    cout<<"New Account Created Successfully.. "<<endl;
}

void Bank_Account::account_info() const
{
    cout<<" Account Number: "<<accountNumber<<endl;
    cout<<"   Account Name: "<<accountName<<endl;
    cout<<"   Account Type: "<<accountType<<endl;
    cout<<"Current Balance: "<<balance<<endl;
}

void Bank_Account::deposite(int amount)
{
    cout<<"Current Balance: "<<balance<<endl;
    cout<<"Deposited Amount: "<<amount<<endl;
    balance = balance + amount;
    cout<<"New Balance: "<<balance;
}

void Bank_Account::withdraw(int amount)
{
    cout<<"Current Balance: "<<balance<<endl;
    cout<<"Withdrawn Amount: "<<amount<<endl;
    balance = balance - amount;
    cout<<"New Balance: "<<balance;
}

void Bank_Account::modify()
{
    cout<<"Modify Account Name : " <<endl;
    cin.ignore();
	cin.getline(accountName,80);
    cout<<"Modify Account Type: "<<endl;
    cin>>accountType;
    accountType = toupper(accountType);
    cout<<"Modify Balance: "<<endl;
    cin>>balance;
}


int Bank_Account::getBalance() const
{
    return balance;
}

int Bank_Account::getAccountNumber() const
{
    return accountNumber;
}

char Bank_Account::getAccountType() const
{
    return accountType;
}

void Bank_Account::allInfo() const
{
    cout<<accountNumber<<setw(10)<<"   "<<accountName<<setw(10)<<"   "<<accountType<<setw(6)<<"  "<<balance<<endl;
}


void open_account();
void deposite_balance(int);
void withdraw_balance(int);
void view_account(int);
void view_all_account();
void account_delete(int);
void account_change(int);

int main()
{
    char menu;
    int id;

    do
    {
        cout<<"\t\t\tBank Management System\n\n\n";
        cout<<" \nMain Menu.  Select Your Option  : \n" <<endl<<endl;
        cout<<" To create new Account : Enter 1 : \n"<<endl;
        cout<<" To view Account Info  : Enter 2 : \n"<<endl;
        cout<<" To Deposit Balance    : Enter 3 : \n"<<endl;
        cout<<" To Withdraw Balance   : Enter 4 : \n"<<endl;
        cout<<" To Delete Account     : Enter 5 : \n"<<endl;
        cout<<" To Change Account     : Enter 6 : \n"<<endl;
        cout<<" To view all AccInfo   : Enter 7 : \n"<<endl;
        cout<<" To Exit Main Menu     : Enter 0 : \n"<<endl;
        cin>>menu;

        switch(menu)
        {
            case '1':
                open_account();
                break;

            case '2':
                cout<<"Enter Account Number: "<<endl;
                cin>>id;
                view_account(id);
                break;

            case '3':
                cout<<"Enter Account Number: "<<endl;
                cin>>id;
                deposite_balance(id);
                break;

            case '4':
                cout<<"Enter Account Number: "<<endl;
                cin>>id;
                withdraw_balance(id);
                break;

            case '5':
                cout<<"Enter Account Number: "<<endl;
                cin>>id;
                account_delete(id);
                break;

            case '6':
                cout<<"Enter Account Number: "<<endl;
                cin>>id;
                account_change(id);
                break;

            case '7':
                view_all_account();
                break;

            case '8':
                cout<<"Thanks. Exiting Main Menu.. "<<endl;
                break;

            default:
                cout<<"You Entered wrong Input, Please ReEnter: "<<endl;
                break;
        }
        cin.ignore();
		cin.get();
    }
    while(menu!='8');
        return 0;
}

// Function definition start

void open_account()
{
    Bank_Account account;
    ofstream writeFile;
    writeFile.open("Bank_Management.dat",ios::binary|ios::app);
    account.create_account();
    writeFile.write(reinterpret_cast<char *> (&account), sizeof(Bank_Account));
    writeFile.close();
}


void view_account(int id)
{
    Bank_Account account;
    ifstream readFile;
    bool flag=false;
    readFile.open("Bank_Management.dat",ios::binary);
    if(readFile.fail())
    {
        cout<<"File Opening Fail.. Retry"<<endl;
        return;
    }

    cout<<"Account Info for Account Number: "<<id<<endl;

        while(readFile.read(reinterpret_cast<char *> (&account), sizeof(Bank_Account)))
        {
            if(account.getAccountNumber()==id)
            {
                account.account_info();
                flag=true;
            }
        }

    readFile.close();
    if(flag==false)
    {
        cout<<"Account Not Matched.. Retry"<<endl;
        return;
    }
}


void deposite_balance(int id)
{
    Bank_Account account;
    bool flag=false;
    fstream readWrite;
    readWrite.open("Bank_Management.dat",ios::binary|ios::in|ios::out);
    if(readWrite.fail())
    {
        cout<<"File Opening Fail.. Retry"<<endl;
        return;
    }
    while(!readWrite.eof()&&(flag==false))
    {
        readWrite.read(reinterpret_cast<char *> (&account),sizeof(Bank_Account));

            if(account.getAccountNumber()==id)
            {
                //cout<<"Current Balance: "<<account.getBalance()<<endl;
                int x;
                cout<<"Enter Amount to be Deposited: (minimum 10) "<<endl;
                cin>>x;
                if(x>=10)
                {
                    account.deposite(x);
                    //cout<<"New Balance: "<<account.getBalance()<<endl;
                }
                else
                    cout<<"Deposit Fail, amount is less than 10.. "<<endl;

                int position = (-1)*static_cast<int>(sizeof(account));
                readWrite.seekp(position,ios::cur);
                readWrite.write(reinterpret_cast<char *> (&account),sizeof(Bank_Account));
                flag=true;
            }

    }
    readWrite.close();
    if(flag==false)
    {
        cout<<"Account Number Does not Matched.. "<<endl;
    }
}

void withdraw_balance(int id)
{
    Bank_Account account;
    bool flag=false;
    fstream readWrite;
    readWrite.open("Bank_Management.dat",ios::binary|ios::in|ios::out);
    if(readWrite.fail())
    {
        cout<<"File Opening Fail.. Retry"<<endl;
        return;
    }
    while(!readWrite.eof()&&(flag==false))
    {
       readWrite.read(reinterpret_cast<char *> (&account),sizeof(Bank_Account));
        if(account.getAccountNumber()==id)
        {
            //cout<<"Current Balance: "<<account.getBalance()<<endl;
            int x;
            cout<<"Enter Amount to be Withdrawn: (minimum 10) "<<endl;
            cin>>x;
            if((((account.getAccountType()=='S')&&((account.getBalance()-x)>=500)&&(x>=10))||((account.getAccountType()=='O')&&((account.getBalance()-x)>=1000)&&(x>=10))))
                account.withdraw(x);
            else
                cout<<"Insufficient Balance.. Please Deposit First."<<endl;

            int position = (-1)*static_cast<int>(sizeof(account));
            readWrite.seekp(position,ios::cur);
            readWrite.write(reinterpret_cast<char *> (&account),sizeof(Bank_Account));
            flag=true;
        }
    }
    readWrite.close();
    if(flag==false)
    {
        cout<<"Account Number Did not Match.. "<<endl;
    }
}

void account_change(int id)
{
    bool flag2 = false;
    fstream readWrite;
    Bank_Account account;
    readWrite.open("Bank_Management.dat",ios::binary|ios::in|ios::out);
    if(!readWrite)
    {
        cout<<"File Opening Fail.. Retry"<<endl;
        return;
    }
    while(!readWrite.eof()&&flag2==false)
    {
        readWrite.read(reinterpret_cast<char *> (&account),sizeof(Bank_Account));

        if(account.getAccountNumber()==id)
        {
            account.modify();
            int position = (-1)*static_cast<int>(sizeof(account));
            readWrite.seekp(position,ios::cur);
            readWrite.write(reinterpret_cast<char *> (&account),sizeof(Bank_Account));
            flag2 = true;
        }
    }
    readWrite.close();
    if(flag2==false)
    {
        cout<<"Account Number Did not Match.. "<<endl;
    }
}

void account_delete(int id)
{
    bool flag=false;
    Bank_Account account;
    ifstream readFile;
    ofstream writeFile;
    readFile.open("Bank_Management.dat",ios::binary);
    if(!readFile)
    {
        cout<<"Account Opening Fail.. Retry"<<endl;
        return;
    }

    writeFile.open("temp.dat",ios::binary);
    readFile.seekg(0,ios::beg);
    while(readFile.read(reinterpret_cast<char *> (&account),sizeof(Bank_Account)))
    {
        if(account.getAccountNumber()!=id)
        {
            writeFile.write(reinterpret_cast<char *> (&account), sizeof(Bank_Account));
        }
    }
    writeFile.close();
    readFile.close();
    remove("Bank_Management.dat");
    rename("temp.dat","Bank_Management.dat");
    cout<<"Account Number: "<<id<<"Has Been Deleted.. "<<endl;
}

void view_all_account()
{
    Bank_Account account;
    ifstream readFile;
    readFile.open("Bank_Management.dat",ios::binary);
    if(!readFile)
    {
        cout<<"Account Opening Fail.. Retry"<<endl;
        return;
    }
    cout<<"All Account List.. "<<endl;
    cout<<"Account_Number | Account_Name | Account_Type | Balance"<<endl<<endl;
    while(readFile.read(reinterpret_cast<char *> (&account), sizeof(Bank_Account)))
        {
            account.allInfo();
        }
    readFile.close();
}


