#include <curses.h>
#include <fstream>
#include "list.h"
using namespace std;
int main()
{
    //записываем текст
    initscr();
    List<List<chtype>*> text;
    List<chtype>* str;
    char ch;
    ifstream fin;
    fin.open("text.txt");
    str=new List<chtype>;
    text.putOn(1,str);
        while(!fin.eof())
        {

            fin.get(ch);
            addch(ch);
            if(ch=='\n')
            {
                str->putOn(str->count()+1,ch);
                str=new List<chtype>;
                text.putOn(text.count()+1,str);

            }
            else
            {
                str->putOn(str->count()+1,ch);
            }

        }
        fin.close() ;
     for(int i=1; i<=text.count(); ++i)
    {
        text.returnDataFrom(i)->print();
    }

    int row=0,column=0;
    row=text.count()-1;
    column=text.getFrom(text.count())->count();
    chtype symbol;
       bool exit=false;
       str=new List<chtype>;
       text.putOn(row+1,str);
       while(!exit)
       {
           //Навигация по тексту
           noecho();
           while(!exit)
           {
               symbol=getch();
               switch (int(symbol))
               {
               case 1:
                   if(column>0)
                   {
                       --column;
                       move(row,column);
                   }
                   else flash() ;
                   break;
               case 4:
                   if(column<COLS&&column<str->count())
                   {
                       ++column;
                       move(row,column);
                   }
                   else flash();
                   break;
               case 23:
                   if(row>0)
                   {
                       --row;
                       str=text.returnDataFrom(row+1);
                       move(row,column);
                   }
                   else flash();
                   break;
               case 19:
                   if(row+1<text.count())
                   {
                       ++row;
                       str=text.returnDataFrom(row+1);
                       move(row,column);
                   }
                   else flash();

                   break;
               case 9: //Редактирование текста
                   while(!exit)
                   {

                       symbol=getch();
                       if(int(symbol)==14)
                           break;
                       if(symbol=='\n')
                       {
                           str->putOn(column,symbol);
                           ++row;
                           str=new List<chtype>;
                           text.putOn(row+1,str);
                           column=0;
                           addch(symbol);

                       }
                       else if(int(symbol)==8)
                       {
                           if(column>0)
                           {
                               --column;
                               move(row,column);
                               delch();
                               str->del(column+1);
                           }
                           else flash() ;

                       }
                       else
                       {
                           str->putOn(column+1,symbol);
                           insch(symbol);
                           ++column;
                           move(row,column);

                       }
                   }
                   break;
                   case 24:
                   exit=true;
                   break;

               }
           }
       }
       clear();
    ofstream fout;
    fout.open("text.txt");
    for(int i=1;i<=text.count();++i)
    {
        for(int j=1;i<=text.returnDataFrom(i)->count();++j)
        fout<<text.returnDataFrom(i)->returnDataFrom(j);
    }
    fout.close();

    refresh();
    return 0;
}
