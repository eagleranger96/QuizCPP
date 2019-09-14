#include "clrscr.h"
#include "lifelines.h"
#include "login.h"
#include "menu.h"
#include "question.h"
#include "quiz.h"
using namespace std;

int main()
{
    Login L;
    Question Qu;
    Quiz Qz;
    Menu Mn;
    int ch = 0, flag = 0, qno;
a:
    clrscr();
    //checking if the user is admin
    if(L.login())
    {
        // user is admin
b:
        clrscr();
        ch = Mn.amenu();
        flag = 1;
    }
    else
    {
        // user is not admin
c:
        clrscr();
        ch = Mn.umenu(L);
        flag = 0;
    }

    if(flag)
    {
        // displaying admin menu
        switch(ch)
        {
        case 11:
            //Enter a new Question
            Qu.acceptq();
            Qz.writeq(Qu);
            goto b;

        case 12:
            //Modify a previous Question
            Qz.modifyq();
            goto b;

        case 13:
            clrscr();
            cout<<"\nEnter the question no to be deleted\n\n";
            cin>>qno;
            Qz.deleteq(qno);
            goto b;

        case 14:
            // View question file from the database
            Qz.viewqf();
            goto b;

        case 2:
            //Modify the credentials
            L.changecr();
            goto b;

        case 3:
            //log out
            goto a;

        case 4:
            goto exit;

        default:
            goto b;
        }
    }
    else
    {
        // displaying user menu
        switch(ch)
        {
        case 1:
            //start Quiz
            Qz.sq();
            goto c;

        case 2:
            //Quiz instructions
            Qz.ins();
            goto c;

        case 3:
            //Log out
            goto a;

        case 4:
            goto exit;

        default:
            goto c;
        }
    }

exit:
    return 0;
}
