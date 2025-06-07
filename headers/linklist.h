#ifndef LINKLIST_H
#define LINKLIST_H
#include <iostream>
#include "cards.h"
using namespace std;
template<class T>
class node
{
private:
    T data;
    node<T>* next;
    node<T>* pre;
public:
    void set_data(T d);
    void set_next(node<T>* t);
    void set_pre(node<T>* t);
    T& get_data();
    node<T>* get_pre();
    node<T>* get_next();
};
template<class T>
class link_list{
private:
    int size;
    node<T>* head;
    node<T>* tail;
public:
    link_list ();
    ~link_list ();
    int get_size();
    node<T>*  get_head();
    void set_head(node<T>*newHead);
    node<T>* get_tail();
    void push(T d);
};

template class link_list<cards>;
template class node<cards>;


#endif // LINKLIST_H
