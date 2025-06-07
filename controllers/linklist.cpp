#include "linklist.h"
#include <iostream>
template <class T>
void node<T>::set_data(T d)
{
    data=d;
}
template <class T>
void node<T>::set_next(node<T>* t)
{
    next=t;
}
template <class T>
void node<T>::set_pre(node<T>* t)
{
    node<T>::pre=t;
}
template <class T>
T& node<T>::get_data()
{
    return node<T>::data;
}
template <class T>
node<T>* node<T>::get_pre()
{
    return node<T>::pre;
}
template <class T>
node<T>* node<T>::get_next()
{
    return next;
}
template <class T>
int link_list<T>::get_size()
{
    return link_list<T>::size;
}
template <class T>
node<T>* link_list<T>::get_head()
{
    return link_list<T>::head;
}

template<class T>
void link_list<T>::set_head(node<T> * newHead)
{
    head=newHead;
}
template <class T>
node<T>* link_list<T>::get_tail()
{
    return link_list<T>::tail;
}
template <class T>
void link_list<T>::push(T d)
{
    node<T>* space=new node<T>;
    space->set_data(d);
    if(link_list<T>::size == 0) {
        space->set_next(nullptr);
        space->set_pre(nullptr);
        link_list<T>::head=space;
        link_list<T>::tail=link_list<T>::head;
    }
    if(link_list<T>::size>0)
    {
        space->set_next(link_list<T>::head);
        link_list<T>::head->set_pre(space);
        space->set_pre(nullptr);
        link_list<T>::head = space;
    }
    link_list<T>::size++;
}
template <class T>
link_list<T>::link_list (){
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
template <class T>
link_list<T>::~link_list (){
    node<T>* tmp, *tp;
    tmp = head;
    if(size>0)
    {while (tmp != nullptr)
        {
            tp = tmp;
            tmp = tmp->get_next();
            delete tp;
        }
    }
    size = 0;
    head = nullptr;
    tail = nullptr;
}
