#include<conio.h>
#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;

struct grammar{
    char p[20];
    char prod[20];
}g[10];

int main()
{
    int i,stpos,k,l,m,p,r,flag=0;
    int np,tspos,cr;

    ifstream inFile;
    char ts[10];
    
    cout <<"\nEnter input text file containing productions: ";
    cin>>ts;
    i=0;
    np=0;
    inFile.open(ts);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    string tp;
    cout << "Productions: \n";
    while(getline(inFile, tp)){ //read data from file object and put it into string.
       cout << tp <<"\n";
        tp.copy(g[i].p,1,0);
    
        tp.copy(g[i].prod,tp.length()-1,3);
        
        i++;np++;
    }
    
    char ip[10];
    cout<<"\nEnter Input:";
    cin>>ip;

    int lip=strlen(ip);
    char stack[10];

    stpos=0;//stack pointer
    i=0;// input string pointer
    char sc; //read char by char
    //move the input
    sc=ip[i];
    stack[stpos]=sc;
    i++;stpos++;
//first char from input string has been moved to the stack
    cout<<"\n\nStack\tInput\tAction";
    do
    {
        r=1;
         
        while(r!=0)
        {
            cout<<"\n";
            for(p=0;p<stpos;p++)
            {
                cout<<stack[p];// stack column
            }

            cout<<"\t";
            for(p=i;p<lip;p++)
            {
                cout<<ip[p];// input column
            }

            if(r==2)
            {
                cout<<"\tReduced";
            }
            else
            {
                cout<<"\tShifted";
            }
            r=0;
           

            //try reducing

            for(k=0;k<stpos;k++)
            {

                for(l=0;l<10;l++)
                {
                    ts[l]='\0';
                }

                tspos=0;
                for(l=k;l<stpos;l++) //removing first character
                {
                    ts[tspos]=stack[l];
                    tspos++;
                }
                int nomat=0;
                //now compare each stack elements with production
                for(m=0;m<np;m++)
                {
                    cr = strcmp(ts,g[m].prod);
                    
                   

                    //if cr is zero, then match is found
                    if(cr==0)
                    {
                        for(l=k;l<10;l++) //removing matched part from stack
                        {
                            stack[l]='\0';
                            
                        }

                        stpos=k;
                        //append to the string
                        strcat(stack,g[m].p);
                        stpos++;
                        r=2;//Reduce string
                    }
                    if(cr!=0)
                    nomat++;// number of times, stack contents have not matched with the productions
                    if(nomat==np && ip[i]=='\0')// matched with none of productions, no more shifts left as buffer is empty, exit
                    flag=1;
                }
            }
        }
        //move the input
        sc=ip[i];
        stack[stpos]=sc;
        i++;stpos++;
        
    }while(strlen(stack)!=1 && flag==0);// exit condition: only 1 element left in stack or all elements of ip buffer have been moved to stack and not fully reduced.

    if(strlen(stack)==1)
    {
        cout<<"\n String Accepted";
       
    }
    else {
        cout<<"\n String Not Accepted";
    }

    inFile.close();
    return 0;

}