#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <cstdio>
using namespace std;

void signup();
void signin();
void Transfer();
void ATM(string name, string pass, int blnc);
int main();
int balance = 0;
int found = 0;

const int maxrow = 50;
int count = 0;
int pre = 0;

// ###################################### ATM ##################################################
// Transfer
void Transfer(string name, string pass, int blnc)
{
    if (blnc == 0)
    {
        cout << name << " your balance is Zero RS Please Recharge";
        exit(0);
    }
    string n, p, n2, p2, nm, cn, cp;
    int amount, fnl, b, b2, cb;
    cout << "Enter name : ";
    cin >> nm;
    // for cheak
    ifstream cheak;
    cheak.open("record.txt");
    while (cheak >> cn >> cp >> cb)
    {
        if (cn == nm)
        {
            found = 1;
            cout << cn << endl;
            continue;
        }
    }
    if (found != 1)
    {
        cout << "User name not found ..." << endl;
        Transfer(name, pass, blnc);
    }
    cout << "Enter amount : ";
    cin >> amount;
    fnl = blnc - amount;
    // for read and write data.
    ifstream myfile;
    ofstream temp2;
    myfile.open("record.txt");
    temp2.open("temp2.txt");

    while (myfile >> n >> p >> b)
    {
        if (n != nm)
        {
            temp2 << n << " " << p << " " << b << endl;
        }
        else
        {

            temp2 << n << " " << p << " " << amount + b << endl;
        }
    }

    ifstream s;
    s.open("temp2.txt");
    ofstream s2;
    s2.open("temp.txt");
    while (s >> n >> p >> b)
    {
        if (n != name)
        {
            s2 << n << " " << p << " " << b << endl;
        }
        else
        {
            s2 << n << " " << p << " " << fnl << endl;
        }
    }
    myfile.close();
    temp2.close();

    ofstream myfile2;
    ifstream temp;

    myfile2.open("record.txt");
    temp.open("temp.txt");

    while (temp >> n2 >> p2 >> b2)
    {

        myfile2 << n2 << " " << p2 << " " << b2 << endl;
    }

    myfile2.close();
    temp2.close();

    cout << "Withdraw Sucessfuly : " << amount << "rs" << endl;
    cout << "Now you current balance is " << fnl << "rs" << endl;
}

// BALANCE CHEAK
void Balance(int b, string n)
{
    system("CLS");
    cout << "----------------------------------------------------------\n";
    cout << n << " your currunt balance is " << b << "rupees." << endl;
    ;
    cout << "----------------------------------------------------------\n\n\n\n\n";
    getch();
}
// WithDraw
void Withdraw(string name, string pass, int blnc)
{
    if (blnc == 0)
    {
        cout << name << " your balance is Zero Please Recharge";
        exit(0);
    }
    string n, p, n2, p2;
    int amount, fnl, b, b2;
    cout << "Enter amount : ";
    cin >> amount;
    cout << blnc;
    if (amount > blnc)
    {
        cout << "Your account does not have  enough balance to Transfer money.";
        Withdraw(name, pass, blnc);
    }
    fnl = blnc - amount;
    // for read and write data.
    ifstream myfile;
    ofstream temp;
    myfile.open("record.txt");
    temp.open("temp.txt");

    while (myfile >> n >> p >> b)
    {
        if (n != name && p != pass)
        {
            temp << n << " " << p << " " << b << endl;
        }
        else
        {
            temp << n << " " << p << " " << fnl << endl;
        }
    }
    myfile.close();
    temp.close();

    ofstream myfile2;
    ifstream temp2;

    myfile2.open("record.txt");
    temp2.open("temp.txt");

    while (temp2 >> n2 >> p2 >> b2)
    {

        myfile2 << n2 << " " << p2 << " " << b2 << endl;
    }

    myfile2.close();
    temp2.close();

    cout << "Withdraw Sucessfuly : " << amount << "rs" << endl;
    cout << "Now you current balance is " << fnl << "rs" << endl;
    exit(0);
}

void ATM(string name, string pass, int blnc)
{
    system("CLS");
    int option;
    cout << "=============================================================================\n";
    cout << "                                ATM\n";
    cout << "(1)==> Balance\n";
    cout << "(2)==> Withdraw\n";
    cout << "(3)==> Transfer\n";
    cout << "(4)==> Exit\n";
    cout << "---------------------------------------------------------------------------\n";
    cout << "Select Option >> ";
    cin >> option;
    switch (option)
    {
    case 1:
        Balance(blnc, name);
        break;
    case 2:
        Withdraw(name, pass, blnc);
    case 3:
        Transfer(name, pass, blnc);
        break;
    default:
        break;
    }
    exit(0);
}
// ###################################### SignUp ##################################################

void signup()
{
    system("CLS");
    string name;
    string pass;
    string n;
    string p;
    int b;
    if (count > 0)
    {
        cout << "User name alredy exist please enter another name" << endl;
    }
    cout << "Enter Username : ";
    cin >> name;

    // For check username alredy exist (or) not.
    ifstream open("record.txt");
    if (open.is_open())
    {
        while (open >> n >> p >> b)
        {
            if (name == n)
            {
                cout << n;
                count++;

                signup();
            }
        }
    }
    open.close();
    cout << "Enter Password : ";
    cin >> pass;

    ofstream file("record.txt", ios::app);
    file << name << " " << pass << " " << balance << endl;

    cout << "Enter space to return home page .....";
    getch();
    main();
}

// ###################################### SignIN ##################################################

void signin()
{
    system("CLS");
    string name;
    string pass;
    string u, p;
    int blnc;
    string line;
    cin.ignore();

    cout << "Enter Username : ";
    cin >> name;
    cout << "Enter Password : ";
    cin >> pass;
    ifstream input("record.txt");
    ifstream inpu("Admin.txt");
    if (input.is_open())

    {
        while (input >> u >> p >> blnc)
        {
            if (u == name && p == pass)
            {
                ATM(name, pass, blnc);
                break;
            }
        }
    }
    if (inpu.is_open())
    {
        while (inpu >> u >> p)
        {
            if (u == name && p == pass)
            {
                cout << "Your Welcome Admin " << endl;
                break;
            }
        }
    }

    cout << "Please cheak the username and password ." << endl;
    cout << "Press Enter to return .";
    getch();
    signin();
    exit(0);
}

// ###################################### Main Funtion ##################################################

int main()
{
    system("CLS");
    int option;
    cout << "                           Home Page" << endl;
    cout << "================================================================\n";
    cout << "MENU\n";
    cout << "1-SignUp" << endl;
    cout << "2-Signin" << endl;
    cout << "3-Save and Exit" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "Select option >>";
    cin >> option;
    switch (option)
    {
    case 1:
        signup();

        break;
    case 2:
        signin();
    
    default:
        break;
    }
}