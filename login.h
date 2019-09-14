#ifndef _LOGIN_H
#define _LOGIN_H

#define cfile "data\\credentials.dat"
#define car_size 50

#include <iostream>
#include <fstream>
using namespace std;

class Login
{
private:
    struct credentials
    {
        char name[car_size], password[car_size];
    };
    credentials c;

    void getpass(char p[], int size)
    {
        char entr = '\r', bksp = '\b';
        int i;
        for(i=0; i<size-1; i++)
        {
            p[i] = getch();
            if(p[i]==bksp)
            {
                cout<<bksp;
                i--;
            }
            else if(p[i]==entr)
            {
                p[i]='\0';
                cout<<'\n';
                break;
            }
            else
            {
                cout<<'*';
            }
        }
        if(i==(size-2))
        {
            p[++i]='\0';
        }
    }

    void readcr()
    {
        ifstream fin;
        fin.open(cfile,ios::in|ios::binary);
        if(fin)
        {
            fin.read((char*)&c,sizeof(c));
        }
        fin.close();
    }

    void writecr()
    {
        ofstream fout;
        fout.open(cfile,ios::out|ios::binary);
        if(fout)
        {
            fout.write((char*)&c,sizeof(c));
        }
        fout.close();
    }

public:
    Login()
    {
        c.name[0] = c.password[0] = '\0';
    }

    int login()
    {
        char namel[car_size], passl[car_size];
logst:
        clrscr();
        readcr();
        int rt = 0;
        cout<<"\n\tWelcome to C++ Quiz\n";
        cout<<"\nEnter your name\n\n";
        cin.sync();
        cin.getline(namel,car_size);
        if(strcmp(namel,c.name)==0)
        {
            cout<<"\nEnter Password\n\n";
            getpass(passl,car_size);
            if(strcmp(passl,c.password)==0)
            {
                rt = 1;
            }
            else
            {
                cout<<"\nFatal Security Error\n\n";
                getch();
                goto logst;
            }
        }
        else
        {
            strcpy(c.name,namel);
            rt = 0;
        }
        return rt;
    }

    void changecr()
    {
        char namep[car_size], namen[car_size], passp[car_size], passn[car_size];
        clrscr();
        cout<<"\nEnter present admin name\n\n";
        cin.sync();
        cin.getline(namep, car_size);
        cout<<"\nEnter new admin name\n\n";
        cin.sync();
        cin.getline(namen, car_size);
        cout<<"\nEnter present password\n\n";
        getpass(passp, car_size);
        cout<<"\nEnter new password\n\n";
        getpass(passn, car_size);

        if(strcmp(c.name,namep)==0 && strcmp(c.password,passp)==0)
        {
            strcpy(c.name,namen);
            strcpy(c.password,passn);
            writecr();
            clrscr();
            cout<<"\nCredentials changed successfully\n";
            getch();
        }

        else
        {
            cout<<"\nWhat nonsense, call the real admin\n";
            getch();
        }
    }

    char* getname()
    {
        return c.name;
    }
};

#endif
