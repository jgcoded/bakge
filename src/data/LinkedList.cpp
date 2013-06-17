/* *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Paul Holden et al. (See AUTHORS)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * */

#ifndef BAKGE_DATA_LINKEDLIST_CPP
#define BAKGE_DATA_LINKEDLIST_CPP

#include <bakge/Bakge.h>

namespace bakge
{

template<class T>
LinkedList<T>::LinkedList()
{
    Head = NULL;
    Tail = NULL;
}


template<class T>
LinkedList<T>::~LinkedList()
{
    /* Iterate list and free memory */
    SingleNode<T>* Node;
    while (Head != NULL) {
        Node = Head;
        Head = Head->GetNext();
        delete Node;
    }
}


template<class T>
T LinkedList<T>::Push(T DataValue)
{
    SingleNode<T>* NewNode;

    /* Create new node */
    NewNode = new SingleNode<T>();
    NewNode->SetData(DataValue);

    /* Move pointers */
    if (Head == NULL) {
        Tail = Head = NewNode;
        NewNode->SetNext(NULL);
    } else {
        NewNode->SetNext(Head);
        Head = NewNode;
    }

    return DataValue;
}


template<class T>
T LinkedList<T>::Pop()
{
    SingleNode<T>* TopNode;
    T DataValue;

    /* What about exceptions? Use default or write our own? */
    if (Head == NULL) {
        throw "LinkedList is empty";
    }

    /* Memorize pointer to free memory */
    TopNode = Head;

    /* Move pointers */
    Head = Head->GetNext();
    if (Head == NULL) {
        Tail = Head;
    }

    /* Memorize return value and free memory */
    DataValue = TopNode->GetData();
    delete TopNode;

    return DataValue;
}


template<class T>
bool LinkedList<T>::IsEmpty()
{
	/* List is empty if Head pointer is NULL */
	return (Head == NULL);
}

} /* bakge */

#endif /* BAKGE_DATA_LINKEDLIST_CPP */
