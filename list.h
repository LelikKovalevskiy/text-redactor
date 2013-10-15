#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <curses.h>
template< class item >
struct Node
{
    item x;
    Node *Next,*Prev;
    Node():Next(0),Prev(0){ };
};
template< class item >
class List
{
private:
    Node<item> *Head,*Tail;
public:
    List():Head(0),Tail(0) {};
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
   for(int i=0;i<x-1;++i)
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


#endif // LIST_H_INCLUDED
