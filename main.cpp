#include <iostream>
#include <fstream>
#include <cstdio>
#include <conio.h>
#include <process.h>
#include <cstring>
#include <cctype>
#include <windows.h>
using namespace std;

#define qo_size 200
#define car_size 50
#define qfile "data\\Questions.dat"
#define cfile "data\\credentials.dat"
#define tfile "data\\temp.dat"

void clrscr()
{
    DWORD n;
    DWORD size;
    COORD coord = {0};
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE h;
    h = GetStdHandle ( STD_OUTPUT_HANDLE );
    GetConsoleScreenBufferInfo ( h, &csbi );
    size = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
    GetConsoleScreenBufferInfo ( h, &csbi );
    FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );
    SetConsoleCursorPosition ( h, coord );
}

fstream f;
ifstream fin;
ofstream fout;

class Question //For Questions
{
    int Qno;
    char Q[qo_size], A[qo_size], B[qo_size], C[qo_size], D[qo_size], Ans;
public:
    Question();
    void acceptq();
    void displayq(int);
    int getqno();
    char getans();
} Qu;

Question::Question() //Constructor
{
    Q[0]='\0';
    A[0]='\0';
    B[0]='\0';
    C[0]='\0';
    D[0]='\0';
    Qno = 0;
    Ans = '\0';
}


void Question::acceptq() //Accepting Question
{
    cout<<"\nEnter Question no\n";
    cin>>Qno;
    cout<<"\nEnter Question\n";
    cin.sync();
    cin.getline(Q,qo_size);
    cout<<"\nEnter Option A\n";
    cin.sync();
    cin.getline(A,qo_size);
    cout<<"\nEnter Option B\n";
    cin.sync();
    cin.getline(B,qo_size);
    cout<<"\nEnter Option C\n";
    cin.sync();
    cin.getline(C,qo_size);
    cout<<"\nEnter Option D\n";
    cin.sync();
    cin.getline(D,qo_size);
    cout<<"\nIndicate correct response\n";
    cin>>Ans;
}

void Question::displayq(int r = 1) //Displaying Question
{
    cout<<"\nQ "<<Qno<<". "<<Q<<endl;
    cout<<"\n\t(A) "<<A<<endl;
    cout<<"\n\t(B) "<<B<<endl;
    cout<<"\n\t(C) "<<C<<endl;
    cout<<"\n\t(D) "<<D<<endl;
    if(r==0)
    {
        cout<<"\nCorrect Answer is \'("<<Ans<<")\'\n";
    }
}

int Question::getqno() //Returning Question no
{
    return Qno;
}

char Question::getans() //Returning correct Answer
{
    return Ans;
}

class Login //For Admin Settings
{
    struct credentials
    {
        char name[car_size], password[car_size];
    } c;
    void getp(char*);
    void readcr();
    void writecr();
public:
    Login();
    int login();
    void changecr();
    char* getname();
} L;

Login::Login() //Constructor
{
    c.name[0] = '\0';
    c.password[0] = '\0';
}

void Login::getp(char* p) //Entering Password
{
    char* s = p;
    while((p-s)<50)
    {
        if(p<s)
            p=s;
        else if((p-s)>=49)
        {
            p = s + 49;
            *p = '\0';
            break;
        }
        *p = getch();
        if(*p=='\b')
        {
            --p;
            cout<<'\b';
            continue;
        }
        else if(*p=='\r')
        {
            *p='\0';
            break;
        }
        else
        {
            cout<<'*';
            ++p;
            continue;
        }
    }
    p=s;
}


void Login::readcr() //Reading Credentials
{
    f.open(cfile,ios::in|ios::binary);
    if(f)
    {
        f.read((char*)&c,sizeof(c));
    }
    f.close();
}

void Login::writecr() //Writing Credentials
{
    f.open(cfile,ios::out|ios::binary);
    if(f)
    {
        f.write((char*)&c,sizeof(c));
    }
    f.close();
}

char* Login::getname() //Accepting Username
{
    char* p = c.name;
    return p;
}

int Login::login() //Login Process
{
    char namel[50], passl[50];
    clrscr();
    readcr();
    int rt = 0;

    cout<<"\n\tWelcome to Great C++ Quiz\n";
    cout<<"\nEnter your name\n";
    cin.sync();
    cin.getline(namel,car_size);

    if(strcmp(namel,c.name)==0)
    {
        cout<<"\nEnter Password\n";
        getp(passl);
        if(strcmp(passl,c.password)==0)
        {
            rt = 1;
        }
        else
        {
            cout<<"\nFatal Security Error\n";
            getch();
            exit(0);
        }
    }
    else
    {
        strcpy(c.name,namel);
        rt = 0;
    }
    return rt;
}

void Login::changecr() //Changing Credentials
{
    char namep[car_size], namen[car_size], passp[car_size], passn[car_size];
    clrscr();
    cout<<"\nEnter present admin name\n";
    cin.sync();
    cin.getline(namep,car_size);
    cout<<"\nEnter new admin name\n";
    cin.sync();
    cin.getline(namen,car_size);
    cout<<"\nEnter present password\n";
    getp(passp);
    cout<<"\nEnter new password\n";
    getp(passn);

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



int amenu() //Admin Menu
{
    int ch;
a:
    clrscr();
    cout<<"\n\tWelcome Administrator\n";
    cout<<"\nEnter your choice(no in bracket)\n";
    cout<<"\n(1) Quiz Modification\n";
    cout<<"\n(2) Credentials Modification\n";
    cout<<"\n(3) Log Out\n";
    cout<<"\n(4) Exit\n";
    cin>>ch;

    if(ch==1)
    {
        clrscr();
        cout<<"\n(1) Enter a new Question\n";
        cout<<"\n(2) Modify a previous Question\n";
        cout<<"\n(3) Delete a Question\n";
        cout<<"\n(4) View Question File\n";
        cout<<"\n(5) Back\n";
        cin>>ch;
        ch = 10 + ch;
        if(ch==15)
            goto a;
    }
    return ch;
}

int umenu() //User Menu
{
    char named[50];
    int ch;
    strcpy(named,L.getname());
    clrscr();
    cout<<"\n\tWelcome "<<named<<endl;
    cout<<"\nEnter your choice(no in bracket)\n";
    cout<<"\n(1) Start Quiz\n";
    cout<<"\n(2) Instructions\n";
    cout<<"\n(3) Log Out\n";
    cout<<"\n(4) Exit\n";
    cin>>ch;
    if(ch==4)
        exit(0);
    return ch;
}

class Quiz //For Conducting quiz
{
public:
    void sq();
    void ins();
    int readq(int);
    void writeq(Question& Que);
    void modifyq();
    void deleteq(int);
    void viewqf();
} Z;


void Quiz::ins() //Quiz Instructions
{
    clrscr();
    cout<<"\n\tWelcome to great c++ quiz\n";
    cout<<"\n\nWhen you play quiz a question will be";
    cout<<" displayed.\nYou just need to select A,B,C, or D and press";
    cout<<" enter from the given options.\nQuiz continues until you";
    cout<<" give a wrong answer.\n For every correct answer you";
    cout<<" get one point.\n\nSo play and enjoy....";
    getch();
    clrscr();
}

void Quiz::sq() //Conducting Quiz
{
    char ans;
    int score = 0, qno=1;
    cout<<"\nGet ready for the quiz...";
    getch();
    clrscr();

    while(Z.readq(qno))
    {
p:
        clrscr();
        Qu.displayq();
        cin>>ans;
        qno++;
        if(tolower(ans)==tolower(Qu.getans()))
        {
            cout<<"\nCorrect Answer\n";
            getch();
            clrscr();
            score++;
        }
        else if(tolower(ans)!='a' && tolower(ans)!='b' && tolower(ans)!='c' && tolower(ans)!='d')
        {
            qno--;
            goto p;
        }
        else
        {
            cout<<"\nWrong Answer\n";
            f.close();
            break;
        }
    }
    cout<<"\nQuiz completed\nYour score is: "<<score<<endl;
    getch();
}

void Quiz::viewqf() //Displaying Question Database
{
    f.open(qfile,ios::in|ios::binary);
    clrscr();
    while(f.read((char*)&Qu,sizeof(Qu)))
    {
        Qu.displayq(0);
    }
    f.close();
    getch();
}

int Quiz::readq(int qno) //Reading Question
{
    int flag = 0;
    f.open(qfile,ios::in|ios::binary);
    while(f.read((char*)&Qu,sizeof(Qu)))
    {
        if(Qu.getqno()==qno)
        {
            flag = 1;
            break;
        }
    }
    f.close();
    if(flag==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void Quiz::writeq(Question& Que) //Writing Question
{
    f.open(qfile,ios::app|ios::binary);
    f.write((char*)&Que,sizeof(Que));
    f.close();
}
void Quiz::deleteq(int qno) //Deleting Question
{
    int flag = 0;
    fin.open(qfile,ios::in|ios::binary);
    fout.open(tfile,ios::out|ios::binary);
    while(fin.read((char*)&Qu,sizeof(Qu)))
    {
        if(Qu.getqno()==qno)
        {
            flag = 1;
            cout<<"\nThe Question you want to delete is\n";
            Qu.displayq(0);
            continue;
        }
        else
        {
            fout.write((char*)&Qu,sizeof(Qu));
        }
    }
    fin.close();
    fout.close();
    remove(qfile);
    rename(tfile,qfile);
    if(flag)
        cout<<"\nSuccessfully Deleted\n";
    else
        cout<<"\nCouldn't find such a Question\n";
}

void Quiz::modifyq() //Modifying Questions
{
    int qno;
    cout<<"\nEnter the question no to modify the question\n";
    cin>>qno;
    fin.open(qfile,ios::in|ios::binary);
    fout.open(tfile,ios::out|ios::binary);

    while(fin.read((char*)&Qu,sizeof(Qu)))
    {
        if(Qu.getqno()==qno)
        {
            cout<<"\nThe Question you want to modify is\n";
            Qu.displayq(0);
            cout<<"\nNow enter the new question\n";
            Qu.acceptq();
            fout.write((char*)&Qu,sizeof(Qu));
            continue;
        }
        else
        {
            fout.write((char*)&Qu,sizeof(Qu));
        }
    }

    fin.close();
    fout.close();
    remove(qfile);
    rename(tfile,qfile);
}

int main() //The Main Function
{
    int ch = 0,
        flag = 0,
        qno;
a:
    clrscr();
    if(L.login())
    {
b:
        ch = amenu();
        flag = 1;
    }
    else
    {
c:
        ch = umenu();
        flag = 0;
    }

    if(flag)
    {
        switch(ch)
        {
        case 11:
            clrscr();
            Qu.acceptq();
            Z.writeq(Qu);
            getch();
            goto b;
        case 12:
            clrscr();
            Z.modifyq();
            getch();
            goto b;
        case 13:
            clrscr();
            cout<<"\n Enter the question no to be deleted\n";
            cin>>qno;
            Z.deleteq(qno);
            getch();
            goto b;
        case 14:
            clrscr();
            Z.viewqf();
            clrscr();
            goto b;
        case 2:
            clrscr();
            L.changecr();
        case 3:
            clrscr();
            goto a;
        case 4:
            exit(0);
        default:
            goto b;
        }
    }
    else
    {
        switch(ch)
        {
        case 1:
            Z.sq();
            getch();
            goto c;
        case 2:
            Z.ins();
            goto c;
        case 3:
            goto a;
        default:
            goto a;
        }
    }
    return 0;
}
