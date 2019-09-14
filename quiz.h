#ifndef _QUIZ_H
#define _QUIZ_H

#define qfile "data\\Questions.dat"
#define tfile "data\\temp.dat"

#include <iostream>
using namespace std;

class Quiz
{
public:
    void sq()
    {
        Question Qu;
        Lifelines li;
        char ans;
        int score = 0, qno=1;
        cout<<"\nGet ready for the quiz...";
        getch();

        while(readq(qno, Qu)) // the quiz is running
        {
p:
            clrscr();
            // Displaying a question
            Qu.displayq();
ga:
            // getting user's response
            cin>>ans;

            if(tolower(ans)==tolower(Qu.getans()))
            {
                cout<<"\nCorrect Answer\n";
                getch();
                score++;
            }
            else if(tolower(ans)!='a' && tolower(ans)!='b' && tolower(ans)!='c' && tolower(ans)!='d' && tolower(ans)!='l')
            {
                // invalid character input
                goto p;
            }
            else if(tolower(ans)=='l')
            {
                // user has chosen a lifeline
                int life=li.lifelineMenu(Qu);

                if(life==1)
                {
                    // user has opted for fifty-fifty
                    li.fifty_fifty(Qu);
                    goto ga;
                }
                else if(life==2)
                {
                    //user has opted for double-dip
                    int res = li.doubledip(Qu);
                    if(res==1)
                    {
                        /*correct answer*/

                        cout<<"\nCorrect Answer\n";
                        getch();
                        score++;

                    }
                    else if(res==2)
                    {
                        //quiz over
                        cout<<"\nWrong Answer\n\n";
                        break;
                    }
                    else if(res==5)
                    {
                        // Lifeline used already
                        qno--;
                    }
                }
                else
                {
                    //user has chosen audience pol

                    li.public_opinion(Qu); // displaying public opinion
                    getch();
                    clrscr();
                    Qu.displayq();
                    goto ga;
                }

            }
            else
            {
                cout<<"\nWrong Answer\n";
                break;
            }
            qno++;
        }
        cout<<"\n\nQuiz completed\n\nYour score is: "<<score<<"\n\n";
        getch();
    }

    void ins() // Quiz instructions
    {
        clrscr();
        cout<<"\n\tWelcome to C++ quiz\n";
        cout<<"\n\nWhen you play quiz a question will be";
        cout<<" displayed.\n\nYou just need to select A,B,C, or D and press";
        cout<<" enter from the given options.\n\nQuiz continues until you";
        cout<<" give a wrong answer.\n\nFor every correct answer you";
        cout<<" get one point.\n";
        cout<<"\nTo use any lifeline for a question press L\n";
        cout<<"\nChoose any lifeline from the given lifeline menu. You can use a lifeline only once\n";
        cout<<"\nSo play and enjoy...\n";
        getch();
        clrscr();
    }

    int readq(int qno, Question& Qu)// reading file in a sequential manner from the database
    {
        ifstream fin;
        int flag = 0;
        fin.open(qfile,ios::in|ios::binary);
        while(fin.read((char*)&Qu,sizeof(Qu)))
        {
            if(Qu.getqno()==qno)
            {
                flag = 1;
                break;
            }
        }
        fin.close();
        return flag;
    }

    void writeq(Question& Que) // writing question in the database
    {
        ofstream fout;
        fout.open(qfile,ios::app|ios::binary);
        fout.write((char*)&Que,sizeof(Que)); //writing one object at a time from the database
        fout.close();
    }

    void modifyq() // function to modify Existing Question
    {
        ifstream fin;
        ofstream fout;
        Question Qu;
        int qno;
        cout<<"\nEnter the question no of the question to modify\n\n";
        cin>>qno;
        fin.open(qfile,ios::in|ios::binary); // current question file
        fout.open(tfile,ios::out|ios::binary);  // making a new question file
        while(fin.read((char*)&Qu,sizeof(Qu)))
        {
            if(Qu.getqno()==qno)
            {
                cout<<"\nThe Question you want to modify is\n\n";
                Qu.displayq(0);
                cout<<"\nNow enter the new question\n";
                Qu.acceptq();
                fout.write((char*)&Qu,sizeof(Qu));
            }
            else
            {
                fout.write((char*)&Qu,sizeof(Qu));
            }
        }
        fin.close();
        fout.close();
        remove(qfile); // removing current question file
        rename(tfile,qfile); // removing current question file and renaming the new file to current one
    }

    void deleteq(int qno) // deleting question from the database
    {
        int flag = 0;
        Question Qu;
        char choice;
        ifstream fin(qfile,ios::in|ios::binary); // opening current question file
        ofstream fout(tfile,ios::out|ios::binary); // making a new question file
        while(fin.read((char*)&Qu,sizeof(Qu)))
        {
            if(Qu.getqno()==qno)
            {
                flag = 1;
                cout<<"\nThe Question you want to delete is\n";
                Qu.displayq(0);
                cout<<"Are You Sure You Want to Delete (Y/N)?\n";
                cin>>choice;
                if(choice=='y' or choice=='Y')
                    continue;
                else
                    fout.write((char*)&Qu,sizeof(Qu));
            }
            else
            {
                fout.write((char*)&Qu,sizeof(Qu));
            }
        }
        fin.close();
        fout.close();
        remove(qfile); // removing the current question file
        rename(tfile,qfile); //renaming the new question file to the current question file
        if(flag)
        {
            // Deletion has occurred
            resetfile(); // Arranging the database sequentially
            cout<<"\nSuccessfully Deleted\n";
        }
        else
            cout<<"\nCouldn't find such a Question\n";
        getch();
    }

    void viewqf() // viewing questions from the database with their answers
    {
        ifstream fin;
        Question Qu;
        fin.open(qfile,ios::in|ios::binary);
        clrscr();
        while(fin.read((char*)&Qu,sizeof(Qu))) // reading one object at a time from the database
        {
            Qu.displayq(0);
        }
        fin.close();
        getch();
    }

    void resetfile()  // function to Arrange database sequentially
    {
        ifstream fin(qfile, ios::in|ios::binary); // current question file
        ofstream fout(tfile, ios::out|ios::binary);  // making a new question file
        Question Qu;
        int qno = 1;
        while(fin.read((char*)&Qu, sizeof(Qu))) // writing current file to new file sequentially
        {
            Qu.setqno(qno);
            fout.write((char*)&Qu, sizeof(Qu));
            qno++;
        }
        fin.close();
        fout.close();
        remove(qfile); // removing current question file
        rename(tfile, qfile); // renaming new question file to the current question file
    }
};

#endif
