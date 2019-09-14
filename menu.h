#ifndef _MENU_H
#define _MENU_H
#include <iostream>
#include "login.h"
using namespace std;

class Menu
{
public:
    int amenu()
    {
        int ch;
a:
        clrscr();
        cout<<"\n\tWelcome Administrator\n";
        cout<<"\nEnter your choice(no in bracket)\n";
        cout<<"\n(1) Quiz Modification\n";
        cout<<"\n(2) Credentials Modification\n";
        cout<<"\n(3) Log Out\n";
        cout<<"\n(4) Exit\n\n";
        cin>>ch;

        if(ch==1)
        {
            clrscr();
            cout<<"\n(1) Enter a new Question\n";
            cout<<"\n(2) Modify a previous Question\n";
            cout<<"\n(3) Delete a Question\n";
            cout<<"\n(4) View Question File\n";
            cout<<"\n(5) Back\n\n";
            cin>>ch;
            ch = 10 + ch;
            if(ch==15)
                goto a;
        }
        return ch;
    }

    int umenu(Login& L)
    {
        char named[car_size];
        int ch;
        strcpy(named,L.getname());
        clrscr();
        cout<<"\n\tWelcome "<<named<<endl;
        cout<<"\nEnter your choice(no in bracket)\n";
        cout<<"\n(1) Start Quiz\n";
        cout<<"\n(2) Instructions\n";
        cout<<"\n(3) Log Out\n";
        cout<<"\n(4) Exit\n\n";
        cin>>ch;
        return ch;
    }
};

#endif
