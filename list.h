#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <curses.h>
template< class item >
struct Node
{
    item x;
    Node *Next,*Prev;
    Node():Next(0),Prev(0) { };
};
template< class item >
class List
{
private:
    Node<item> *Head,*Tail,*cursor;
public:
    List():Head(0),Tail(0),cursor(Head) {};
    List(List &orig,int):Head(orig.Head),Tail(orig.Tail)
    {
        orig.Head=0;
        orig.Tail=0;
    }
    ~List();
    item getFrom(int x);
    void del(int x);
    item returnDataFrom(int x);
    void putOn(int x,item c);
    int count();
    void sort(bool (*compare)(item , item )) ;
    void print();
    /////////////////Для текст. редактора////////////////
    Node<item>* return_cursor();
    Node<item>* return_tail();
    void cursor_right();
    void cursor_left();
    void del_on_cursor();
    void put_on_cursor(item);
    List* copy(Node<item>*,Node<item>*);
    List* cut(Node<item>*,Node<item>*);
    void past_on_cursor(List<item>*);
    void cursor_begin();
    int cursor_pos();
    void set_cursor_pos(int);
};
template< class item >
List <item> ::~List()
{
    while (Head)
    {
        Tail=Head->Next;
        delete Head;
        Head=Tail;
    }
}
template< class item >
int List <item>::count()
{
    int count=0;
    Node <item>* temp=Head;
    while(temp)
    {
        ++count;
        temp=temp->Next;

    }
    return count;
}
template< class item >
item List <item>::getFrom(int y)
{
    Node<item> *temp;
    temp=Head;
    item data_temp;
    for(int i=0; i<y-1; ++i)
    {
        temp=temp->Next;
    }
    if(Head==Tail && Tail==temp)
    {
        data_temp=temp->x;
        Head=Tail=0;
    }
    else if (temp==Head)
    {
        Head=Head->Next;
        Head->Prev=0;
        data_temp=temp->x;
    }
    else if(temp==Tail)
    {
        Tail=Tail->Prev;
        Tail->Next=0;
        data_temp=temp->x;
    }
    else
    {
        Node<item> *next=temp->Next;
        Node<item> *previous=temp->Prev;
        previous->Next=temp->Next;
        next->Prev=temp->Prev;
        data_temp=temp->x;
    }
    temp=0;
    delete temp;
    return data_temp;

}
template <class item>
void List<item>::del(int x)
{
    Node<item>*temp=Head;
    for(int i=0; i<x-1; ++i)
    {
        temp=temp->Next;
    }
    if(Head==Tail && Tail==temp)
    {
        Head=Tail=0;
    }
    else if (temp==Head)
    {
        Head=Head->Next;
        Head->Prev=0;
    }
    else if(temp==Tail)
    {
        Tail=Tail->Prev;
        Tail->Next=0;
    }
    else
    {
        Node<item> *next=temp->Next;
        Node<item> *previous=temp->Prev;
        previous->Next=temp->Next;
        next->Prev=temp->Prev;
    }
    temp=0;
    delete temp;
}
template< class item >
void List<item>::putOn(int x,item c)
{
    Node<item> *temp=new Node<item>;
    temp->x=c;
    if(x==1)
    {
        temp->Prev=0;
        temp->Next=0;
        if(Head!=0)
        {
            temp->Next=Head;
            Head->Prev=temp;
            Head=temp;
        }
        else
        {
            Head=Tail=temp;
        }
    }
    else if(x==count()+1)
    {

        temp->Next=0;
        temp->Prev=Tail;
        Tail->Next=temp;
        Tail=temp;
    }
    else
    {
        Node<item> *previous=Head;
        for(int i=0; i<x-2; ++i)
            previous=previous->Next;
        temp->Next=previous->Next;
        temp->Next->Prev=temp;
        temp->Prev=previous;
        previous->Next=temp;
    }
}
template< class item >
void List<item>::sort(bool (*compare)(item , item
                                     ))
{
    List<item> Sorted;
    while(Head)
    {
        item tempSorting=getFrom(1);
        int i;
        int tmpCounter=Sorted.count();
        Node<item>* tempSorted=Sorted.Head;
        for(i=1; i<=tmpCounter; ++i)
        {

            if(compare(tempSorting,tempSorted->x))
                break;
            tempSorted=tempSorted->Next;

        }
        Sorted.putOn(i,tempSorting);
    }
    Head=Sorted.Head;
    Tail=Sorted.Tail;

}
template< class item >
item List <item>::returnDataFrom(int y)
{
    Node<item>* temp=Head;
    for(int i=0; i<y-1; ++i)
    {
        temp=temp->Next;
    }
    return temp->x;

}
///////////////////////////Для текст. редактора//////////////
template< class item >
Node<item>* List<item>::return_cursor()
{
    return cursor;
}
template< class item >
Node<item>* List<item>::return_tail()
{
    return Tail;
}
template< class item >
void List<item>::print()
{
    Node<item>*tmp=Head;
    while(tmp!=0)
    {

        addch(tmp->x);
        tmp=tmp->Next;

    }
}
template < class item >
void List<item>::cursor_right()
{
    if(cursor->Next==0)
        ;
    else
        cursor=cursor->Next;
}
template < class item >
void List<item>::cursor_left()
{
    if(cursor->Prev==0)
        ;
    else
        cursor=cursor->Prev;
}
template < class item >
void List<item>::del_on_cursor()
{
    if(cursor==Head&&this->count()==1)
    {
        delete cursor;
        Head=Tail=cursor=0;
    }
    else if(cursor==Head)
    {
        Head->Next->Prev=0;
        Head=Head->Next;
        delete cursor;
        cursor=Head;
    }
    else if(cursor==Tail)
    {
        Tail->Prev->Next=0;
        Tail=Tail->Prev;
        delete cursor;
        cursor=Tail;
    }
    else
    {
        Node<item>*temp=cursor;
        cursor=cursor->Next;
        temp->Next->Prev=temp->Prev;
        temp->Prev->Next=temp->Next;
        temp=0;
        delete temp;
    }

}
template < class item >
void List<item>::put_on_cursor(item c)
{
    Node<item> *temp;
    temp=new Node<item>;
    temp->x=c;
    if(cursor==0)
    {
        Head=Tail=temp;
        cursor=Head;
    }
    else if (cursor==Head)
    {
        Head->Prev=temp;
        temp->Next=Head;
        Head=temp;
    }
    else
    {
        temp->Prev=cursor->Prev;
        cursor->Prev->Next=temp;
        cursor->Prev=temp;
        temp->Next=cursor;

    }
}
template < class item >
List<item>* List<item>::copy(Node<item>*l,Node<item>*r)
{
    List<item>*temp=new List<item>;
    while(1)
    {
        //
        if(l==r)
        {
            temp->putOn(temp->count()+1,r->x);
            break;
        }
        temp->putOn(temp->count()+1,l->x);
        l=l->Next;

    }
    return temp;
}
template < class item >
List<item>* List<item>::cut(Node<item>*l,Node<item>*r)
{
    if(l==Head&&r==Tail)
    {
        Head=Tail=0;
    }
    else
    if(l==Head)
    {
        Head=r->Next;
        r->Next->Prev=0;
    }
    else if(r==Tail)
    {
        Tail=l->Prev;
        l->Prev->Next=0;
    }
    else
    {
        l->Prev->Next=r->Next;
        r->Next->Prev=l->Prev;
    }
    List<item>*temp=new List<item>;
    Node<item>* t;
    while(1)
    {
        if(l==r)
        {
            temp->putOn(temp->count()+1,r->x);
            t=l;
            delete t;
            break;
        }
        temp->putOn(temp->count()+1,l->x);
        t=l;
        l=l->Next;
        delete t;
    }
    return temp;
}
template <class item>
void List<item>::past_on_cursor(List<item>*pasted)
{
    if(cursor==0)
    {
        Head=pasted->Head;
        Tail=pasted->Tail;
    }
    else if(cursor==Head&&cursor==Tail)
    {
        Head=pasted->Head;
        pasted->Tail->Next=cursor;
        cursor->Prev=pasted->Tail;
    }
    else if(cursor==Head)
    {
        pasted->Tail->Next=Head;
        Head->Prev=pasted->Tail;
        Head=pasted->Head;
    }
    else if(cursor==Tail)
    {
        Tail->Prev->Next=pasted->Head;
        pasted->Head=Tail->Prev;
        pasted->Tail->Next=Tail;
        Tail->Prev=pasted->Tail;
    }
    else
    {
        cursor->Prev->Next=pasted->Head;
        pasted->Head->Prev=cursor->Prev;
        cursor->Prev=pasted->Tail;
        pasted->Tail->Next=cursor;
    }
}
template <class item>
void List<item>::cursor_begin()
{
    if(Head!=0)
        cursor=Head;
}
template <class item>
int List<item>::cursor_pos()
{
    Node<item>*tmp=Head;
    int count=1;
    while(tmp!=cursor)
    {
        ++count;
        tmp=tmp->Next;
    }
    return count;
}
template <class item>
void List<item>::set_cursor_pos(int p)
{
    Node<item>*temp=Head;
    for(int i=0; i<p-1; ++i)
        temp=temp->Next;
    cursor=temp;
}
#endif // LIST_H_INCLUDED
