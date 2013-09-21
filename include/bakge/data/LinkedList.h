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

#ifndef BAKGE_DATA_LINKEDLIST_H
#define BAKGE_DATA_LINKEDLIST_H

#include <bakge/Bakge.h>

namespace bakge
{

template<class T>
class LinkedList
{

public:

    LinkedList()
    {
        Head = NULL;
        Tail = NULL;
    }

    ~LinkedList()
    {
        Clear();
    }

    T Push(T Value)
    {
        SingleNode<T>* NewNode;

        /* Create new node */
        NewNode = new SingleNode<T>();
        NewNode->Data = Value;

        /* Move pointers */
        if (Head == NULL) {
            Tail = Head = NewNode;
            NewNode->Next = NULL;
        } else {
            NewNode->Next = Head;
            Head = NewNode;
        }

        return Value;
    }

    T Pop()
    {
        SingleNode<T>* TopNode;
        T DataValue;

        /* Memorize pointer to free memory */
        TopNode = Head;

        /* Move pointers */
        Head = Head->Next;
        if (Head == NULL) {
            Tail = Head;
        }

        /* Memorize return value and free memory */
        DataValue = TopNode->Data;
        delete TopNode;

        return DataValue;
    }

    T BGE_NCP operator[](int At) const
    {
        SingleNode<T>* Pos = Head;

        while(Pos--)
            Pos = Pos->Next;

        return Pos->Data;
    }

    bool IsEmpty() const
    {
        /* List is empty if Head pointer is NULL */
        return (Head == NULL);
    }

    /* Delete the entire contents of the list */
    void Clear()
    {
        /* Iterate list and free memory */
        SingleNode<T>* Node;
        while (Head != NULL) {
            Node = Head;
            Head = Head->Next;
            delete Node;
        }
    }


protected:

    SingleNode<T>* Head;
    SingleNode<T>* Tail;

}; /* LinkedList */

} /* bakge */

#endif /* BAKGE_DATA_LINKEDLIST_H */
