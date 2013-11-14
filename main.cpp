#ifndef LIST_H_INCLUDED
#include <curses.h>
#include <fstream>
#include "list.h"
#include <iostream>
using namespace std;

int main()
{
    bool exit=false;
    bool cut=false;
    bool copy=false;
    char symbol;
    int cursor_pos;
    Node<char>*left;
    Node<char>*right;
    List<char>*temp;
    List<char>*str;
    str=new List<char>;
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
            in.get(symbol);
            if(in.eof())
                break;
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
            if(str->cursor_pos()==str->count()&&str->return_cursor()->x!=' ')
            {
                str->putOn(str->count()+1,' ');
            }
            if(str->cursor_pos()<str->count())
            {
                str->cursor_right();
                move(text.cursor_pos()-1,str->cursor_pos()-1);
            }
            else flash();
            break;
        case 23:
            if(text.cursor_pos()-1>0)
            {
                if (str->cursor_pos()<=text.return_cursor()->Prev->x->count())
                {
                    int tmp=str->cursor_pos();
                    text.cursor_left();
                    str=text.return_cursor()->x;
                    str->set_cursor_pos(tmp);
                    move(text.cursor_pos()-1,str->cursor_pos()-1);
                }
                else if(text.return_cursor()->Prev->x->count()==0)
                {
                    text.cursor_left();
                    str=text.return_cursor()->x;
                    move(text.cursor_pos()-1,0);
                }
                else flash();
            }
            else flash();
            break;
        case 19:
            if(text.cursor_pos()<text.count())
            {
                if (str->cursor_pos()<=text.return_cursor()->Next->x->count())
                {
                    int tmp=str->cursor_pos();
                    text.cursor_right();
                    str=text.return_cursor()->x;
                    str->set_cursor_pos(tmp);
                    move(text.cursor_pos()-1,str->cursor_pos()-1);
                }
                else if(text.return_cursor()->Next->x->count()==0)
                {
                    text.cursor_right();
                    str=text.return_cursor()->x;
                    move(text.cursor_pos()-1,0);
                }
                else flash();
            }
            else flash();
            break;
        case 24://Вырезать
            if(cut==false)
            {
                left=str->return_cursor();
                cut=true;
                cursor_pos=str->cursor_pos();
            }
            else
            {
                right=str->return_cursor();
                temp=str->cut(left,right);
                clear();
                move(0,0); //очищаем и распечатываем
                for(int i=1; i<=text.count(); ++i)
                {
                    for(int j=1; j<=text.returnDataFrom(i)->count(); ++j)
                        addch(text.returnDataFrom(i)->returnDataFrom(j));
                    addch('\n');
                }
                cut=false;
                str->set_cursor_pos(cursor_pos);
                move(text.cursor_pos()-1,str->cursor_pos()-1);
            }
            break;
        case 3://Копировать
            if(copy==false)
            {
                left=str->return_cursor();
                copy=true;
            }
            else
            {
                right=str->return_cursor();
                temp=str->copy(left,right);
                clear();
                move(0,0); //очищаем и распечатываем
                for(int i=1; i<=text.count(); ++i)
                {
                    for(int j=1; j<=text.returnDataFrom(i)->count(); ++j)
                        addch(text.returnDataFrom(i)->returnDataFrom(j));
                    addch('\n');
                }
                copy=false;
                move(text.cursor_pos()-1,str->cursor_pos()-1);
            }
            break;
        case 22:
            str->past_on_cursor(temp);
            clear();
                move(0,0); //очищаем и распечатываем
                for(int i=1; i<=text.count(); ++i)
                {
                    for(int j=1; j<=text.returnDataFrom(i)->count(); ++j)
                        addch(text.returnDataFrom(i)->returnDataFrom(j));
                    addch('\n');
                }
                move(text.cursor_pos()-1,str->cursor_pos()-1);
                break;
        case 9: //Редактирование текста
            while(1)
            {
                symbol=getch();
                if(int(symbol)==14)
                    break;
                if(int(symbol)==8)/////удаление символа или строки
                {
                    if(str->count()>0)
                    {
                        delch();
                        str->del_on_cursor();
                    }
                    else if(text.count()>1)
                    {
                        text.del_on_cursor();
                        str=text.return_cursor()->x;
                        //////////////////////////////
                        clear();
                        move(0,0); //очищаем и распечатываем
                        for(int i=1; i<=text.count(); ++i)
                        {
                            for(int j=1; j<=text.returnDataFrom(i)->count(); ++j)
                                addch(text.returnDataFrom(i)->returnDataFrom(j));
                            addch('\n');
                        }
                        str->cursor_begin();
                    }

                    move(text.cursor_pos()-1,str->cursor_pos()-1);
                }

                else if(int(symbol)==10) //Перевод строки /+-
                {
                    if(str->cursor_pos()==1)
                    {
                        str=new List<char>;
                        text.put_on_cursor(str);
                    }
                    else if(str->cursor_pos()==str->count())
                    {
                        str=new List<char>;
                        text.putOn(text.cursor_pos()+1,str);
                        text.cursor_right();
                        str=text.return_cursor()->x;
                    }
                    else
                    {
                        left=str->return_cursor();
                        right=str->return_tail();
                        temp=str->cut(left,right);
                        str=new List<char>;
                        text.putOn(text.cursor_pos()+1,str);
                        text.cursor_right();
                        str=text.return_cursor()->x;
                        str->past_on_cursor(temp);
                        str->cursor_begin();

                    }
                    move(0,0);
                    for(int i=1; i<=text.count(); ++i)
                    {
                        for(int j=1; j<=text.returnDataFrom(i)->count(); ++j)
                            addch(text.returnDataFrom(i)->returnDataFrom(j));
                        addch('\n');
                    }

                    move(text.cursor_pos()-1,str->cursor_pos()-1);

                }
                else
                {
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
        case 5 :
            exit=true;
            break;

        }
    }
    ofstream fout;
    fout.open("text.txt");
    for(int i=1; i<=text.count(); ++i)
    {
        for(int j=1; j<=text.returnDataFrom(i)->count(); ++j)
            fout<<text.returnDataFrom(i)->returnDataFrom(j);
        fout<<'\n';
    }
    fout.close();
    // ctrl+x =24; ctrl+c=3 ctrl+e = 5 ctrl+v=22
    refresh();
    return 0;
}
