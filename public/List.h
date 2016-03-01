#ifndef LIST_H

#define LIST_H



#include <iostream>;

using namespace std;

#include <assert.h>

//#include "List.h"


#ifdef HARVESTDLL_EXPORTS

#define DLLCLASS   __declspec( dllexport )

#else

#define DLLCLASS   __declspec( dllexport )

#endif



template <class T>

struct Node {


        T data;

        Node* link;

};









template<class T> class DLLCLASS ListIterator;

template<class T> class DLLCLASS List;



template <class T>

class List {

public :

    List();

    ~List();

    void reset();

	Node<T>* gethead();



    void append(const T& data);

    T remove();

    int length();

    int isMember(const T& data);

    void dump();

    friend class ListIterator<T>;

    Node<T>* head;

private :

    Node<T>* tail;

    int count;

};



template <class T>

class ListIterator {

public :

    ListIterator(const List<T>& tl);

    //ListIterator(const List<T>& tl, int dummy);

    ListIterator(const ListIterator<T>& it);

    int more();

    T current();

    void advance();

private :

    Node<T>* p;

};



template <class T>

List<T>::List() {

    head = 0;

    tail = 0;

    count = 0;

}



template <class T>

List<T>::~List() {

    reset();

}



template <class T>

void List<T>::reset()
{

    Node<T>* p;

    while (head) 
	{

        p = head;

        head = head->link;

        delete p;

    }

    count = 0;

}



//added by Vera April, 2004

template <class T>

Node<T>* List<T>::gethead() 

{

   return head;

}





template <class T>

void List<T>::append(const T &data) {

    Node<T>* p = new Node<T>; assert(p);

	//unique_ptr< Node<T> > p(new Node<T>);

    p->data = data;

    p->link = 0;

    if (!head) {

        head = p;

        tail = p;

    } else {

        tail->link = p;

        tail = p;

    }

    count++;


}



template <class T>

T List<T>::remove() {

    assert(head);

    T data = head->data;

    Node<T>* oldHead = head;

    head = head->link;

    delete oldHead;

    count--;

    return data;

}



template <class T>

int List<T>::length() {

    return count;

}



template <class T>

int List<T>::isMember(const T& data) {

    Node<T>* p = head;

    while (p) {

        if (p->data == data) return 1;

        p = p->link;

    }

    return 0;

}



template <class T>

void List<T>::dump() {

    cout << "count = " << count << endl;

    cout << "head -> ";

    Node<T>* p = head;

    while (p) {

        cout << p->data << " ";

        p = p->link;

    }

    cout << endl;

}



//template <class T>

//class ListIterator {

//public :

//    ListIterator(const List<T>& tl) : p(tl.head) {}

//    int more() {return p != 0;}

//    T current() {return p->data;}

//    void advance() {if (p) p = p->link;}

//private :

//    Node<T>* p;

//};















template <class T> 

ListIterator<T>::ListIterator(const List<T>& tl) : p(tl.head) {}



//template <class T>

//ListIterator<T>::ListIterator(const List<T>& tl, int dummy) : p(tl.tail) {}



template <class T>

ListIterator<T>::ListIterator(const ListIterator<T>& it) : p(it.p) 

{

	

}



template <class T>

int ListIterator<T>::more() {

    return p != 0;

}



template <class T>

T ListIterator<T>::current() {

    return p->data;

}



template <class T>

void ListIterator<T>::advance() {

    if (p) p = p->link;

}







#undef DLLCLASS

#endif



