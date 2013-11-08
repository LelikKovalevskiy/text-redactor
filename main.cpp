#include <curses.h>
#include <fstream>
#include "list.h"
using namespace std;

int main()
{
    bool exit=false;
    char symbol;
    Node<char>*left;
    Node<char>*right;
    List<char>*temp;
    List<char>*str;
    initscr();
    List<List<char>*> text;
    ifstream in;
    in.open("text.txt");
    if(in.is_open())
    {
        str=new List<char>;
        text.putOn(1,str);
        while(!in.eof())
        {
            str->cursor_begin();
            if(!in.eof())
            in.get(symbol);
            if(symbol=='\n')
            {
                str=new List<char>;
                text.putOn(text.count()+1,str);
            }
            else
            {
                str->putOn(str->count()+1,symbol);
            }

        }

    }
    for(int i=1;i<=text.count();++i)
    {
        text.returnDataFrom(i)->putOn( text.returnDataFrom(i)->count()+1,' ');
    }
    text.cursor_begin();
    text.return_cursor()->x->cursor_begin();
    in.close();

    for(int i=1; i<=text.count(); ++i)
    {
        for(int j=1; j<=text.returnDataFrom(i)->count(); ++j)
            addch(text.returnDataFrom(i)->returnDataFrom(j));
        addch('\n');
    }

    move(text.cursor_pos()-1,str->cursor_pos()-1);
    noecho();
    str=text.return_cursor()->x;
    while(!exit)
    {
        symbol=getch();
        switch(int(symbol))
        {
            //Режим навигации
        case 1:
            if(str->cursor_pos()-1>0)
            {
                str->cursor_left();
                move(text.cursor_pos()-1,str->cursor_pos()-1);
            }
            else flash();
            break;
        case 4:
            if(str->cursor_pos()!=str->count())
            {
                str->cursor_right();
                move(text.cursor_pos()-1,str->cursor_pos()-1);
            }
            else flash();
            break;
        case 23:
            if(text.cursor_pos()-1>0)
            {
                text.cursor_left();
                str=text.return_cursor()->x;
                move(text.cursor_pos()-1,str->cursor_pos()-1);
            }
            else flash();
            break;
        case 19:
            if(text.return_cursor()->Next!=0)
            {
                text.cursor_right();
                str=text.return_cursor()->x;
                move(text.cursor_pos()-1,str->cursor_pos()-1);
            }
            else flash();
            break;
             case 9: //Редактирование текста
                 while(1)
                 {
                     symbol=getch();
                     if(int(symbol)==14)
                         break;
                     if(int(symbol)==8&&str->count()!=0)/////удаление символа или строки
                     {
                         if(str->cursor_pos()==str->count())
                         {
                             str->cursor_left();
                         }
                         else if(str->count()==1) //Если остался только знак \n
                         {
                             delch();
                             str->del_on_cursor();
                             if(text.count()!=1)//Если строка не единственна
                             {
                                 text.del_on_cursor();
                                 clear();
                                 move(0,0); //очищаем и распечатываем
                                 for(int i=1; i<=text.count(); ++i)
                                 {
                                     for(int j=1; j<=text.returnDataFrom(i)->count(); ++j)
                                         addch(text.returnDataFrom(i)->returnDataFrom(j));
                                 }
                             }

                         }
                         else // если не последний знак в строке
                         {
                             delch();
                             str->del_on_cursor();
                         }
                         move(text.cursor_pos()-1,str->cursor_pos()-1);

                     }
                     else   //если ввелённая клавиша не "удалить", то печатаем
                     {


                         if(str->cursor_pos()==1)
                         {
                             str->put_on_cursor(symbol);
                             str->cursor_right();
                         }
                         if(str->count()==0)
                         {
                             str->put_on_cursor(' ');
                             str->put_on_cursor(symbol);
                             str->cursor_right();
                         }
                         else
                         {

                             str->put_on_cursor(symbol);

                         }
                         insch(symbol);
                         move(text.cursor_pos()-1,str->cursor_pos()-1);
                     }
                 }
                 break;
             case 24:
                 exit=true;
                 break;
                 */


        }
    }
    printw("%d\n",text.count());
    printw("%d",str->count());

    ofstream fout;
    fout.open("text.txt");
    for(int i=1; i<=text.count(); ++i)
    {
        for(int j=1; j<=text.returnDataFrom(i)->count(); ++j)
            fout<<text.returnDataFrom(i)->returnDataFrom(j);
    }
    fout.close();
    refresh();
    return 0;
}
    
