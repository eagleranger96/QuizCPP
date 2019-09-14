#ifndef _QUESTION_H
#define _QUESTION_H

#define qo_size 200

#include <iostream>
#include <conio.h>
using namespace std;

class Question
{
private:
    int Qno;
    char Q[qo_size], A[qo_size], B[qo_size], C[qo_size], D[qo_size], Ans;
public:
    Question() //Intializing everything with null
    {
        Qno = 0;
        Q[0] = A[0] = B[0] = C[0] = D[0] = Ans = '\0';
    }

    void acceptq() //Adding a new Question to database
    {
        clrscr();

        cout<<"\nEnter Question no\n\n";
        cin>>Qno;
        cout<<"\nEnter Question\n\n";
        cin.sync();
        cin.getline(Q, qo_size);
        cout<<"\nEnter Option A\n\n";
        cin.sync();
        cin.getline(A, qo_size);
        cout<<"\nEnter Option B\n\n";
        cin.sync();
        cin.getline(B, qo_size);
        cout<<"\nEnter Option C\n\n";
        cin.sync();
        cin.getline(C, qo_size);
        cout<<"\nEnter Option D\n\n";
        cin.sync();
        cin.getline(D, qo_size);
        cout<<"\nIndicate correct response\n\n";
        cin>>Ans;

        cout<<"\nPress any key to continue...";
        getch();
    }

    void displayq(int r = 1) // displaying question from the database
    {
        cout<<"\nQ "<<Qno<<". "<<Q<<"\n";
        cout<<"\n\t(A) "<<A<<"\n";
        cout<<"\n\t(B) "<<B<<"\n";
        cout<<"\n\t(C) "<<C<<"\n";
        cout<<"\n\t(D) "<<D<<"\n";
        if(r==0)
        {
            cout<<"\nCorrect Answer is ("<<Ans<<")\n";
        }
    }

    void displayqu(char op1,char op2) // displaying Question after using lifeline
    {
        cout<<"\nQ "<<Qno<<". "<<Q<<"\n";
        if('a'==op1 || 'a'==op2)
            cout<<"\n\t(A) "<<A<<"\n";
        else
            cout<<endl<<endl;
        if('b'==op1 || 'b'==op2)
            cout<<"\n\t(B) "<<B<<"\n";
        else
            cout<<endl<<endl;
        if('c'==op1 || 'c'==op2)
            cout<<"\n\t(C) "<<C<<"\n";
        else
            cout<<endl<<endl;
        if('d'==op1 || 'd'==op2)
            cout<<"\n\t(D) "<<D<<"\n";
        else
            cout<<endl<<endl;

    }

    int getqno() // returning the question no of current Question
    {
        return Qno;
    }

    void setqno(int qno)  //seting the question no.
    {
        Qno = qno;
    }

    char getans() // returning the ans of the current question
    {
        return Ans;
    }
};

#endif
