#ifndef _LIFELINES_H
#define _LIFELINES_H

#include <ctime>
#include "question.h"

class Lifelines
{
private:
    bool ffused, ddused, poused;
public:
    Lifelines() // setting all lifelines to not used
    {
        ffused = ddused = poused = false;
    }

    int lifelineMenu(Question& Qu)
    {
        // displaying the lifeline Menu

        clrscr();
        cout<<"\tLifelines\n\n";
        cout<<"\t(1) 50-50\n\n";
        cout<<"\t(2) Double dip\n\n";
        cout<<"\t(3) Audience Poll\n\n";
        int temp;
        cin>>temp;
        return temp;
    }

    void fifty_fifty(Question& Qu)
    {
        // fifty fifty lifeline
        if(ffused)
        {
            // lifeline already used
            cout<<"\nLifeline used\n\n";
            getch();
            clrscr();
            Qu.displayq();
            return;
        }
        // lifeline not used
        srand(time(NULL));
        ffused = true;
        char ans = Qu.getans();
        char randomAnswers[4]= {'a','b','c','d'};
        int t=rand()%4; // generating a random answer
        while(randomAnswers[t]==ans)   // while randomAnswer is same as the right answer
        {
            t=rand()%4;
        }


        clrscr();

        Qu.displayqu(randomAnswers[t],ans); // displaying the fifty fifty Menu
    }

    int doubledip(Question& Qu)
    {

        if(ddused)
        {
            // lifeline already used

            cout<<"\nLifeline used\n";
            getch();
            return 5;
        }
        //lifeline used
        char ans;
        ddused = true;
ddst:
        clrscr();
        Qu.displayq();
        cout<<"\nEnter your first answer\n\n";
        cin>>ans;
        if(tolower(ans)==Qu.getans())
            return 1;
        else if(tolower(ans)=='l')
        {
            cout<<"\nYou cannot use lifelines while using double dip\n\n";
            getch();
            goto ddst;
        }
        else if(tolower(ans)!='a' && tolower(ans)!='b' && tolower(ans)!='c' && tolower(ans)!='d' && tolower(ans)!='l')
            goto ddst;
        else
        {
            cout<<"\nWrong answer\n";
            getch();
        }

ddnt:
        clrscr();
        Qu.displayq();
        cout<<"\nEnter your second answer\n\n";
        cin>>ans;
        if(tolower(ans)==Qu.getans())
            return 1;
        else if(tolower(ans)=='l')
        {
            cout<<"\nYou cannot use lifelines while using double dip\n\n";
            getch();
            goto ddnt;
        }
        else if(tolower(ans)!='a' && tolower(ans)!='b' && tolower(ans)!='c' && tolower(ans)!='d' && tolower(ans)!='l')
            goto ddnt;
        else
        {
            cout<<"\nWrong answer\n";
            getch();
            return 2;
        }

    }

    void public_opinion(Question& Qu) // Audience pol lifeline
    {
        if(poused)
        {
            // lifeline used
            cout<<"\nLifeline used\n\n";
            getch();
            clrscr();
            Qu.displayq();
            return;
        }
        // lifeline not used
        poused=true;
        int a,b,c,d;
        a = b = c = d = 0;
        if(Qu.getans()=='a')
            a+=20;
        if(Qu.getans()=='b')
            b+=20;
        if(Qu.getans()=='c')
            c+=20;
        if(Qu.getans()=='d')
            d+=20;
        a = (a+rand())%100;
        b = (b+rand())%(100-a);
        c = (c+rand())%(100-a-b);
        d = 100-a-b-c;
        cout<<"\nAudience poll says\n";
        cout<<"\n(A) --> "<<a<<"% \n";
        cout<<"\n(B) --> "<<b<<"% \n";
        cout<<"\n(C) --> "<<c<<"% \n";
        cout<<"\n(D) --> "<<d<<"% \n";
    }
};

#endif
