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

#include <stdio.h>
#include <stdlib.h>
#include <bakge/Bakge.h>

int main(int argc, char* argv[])
{
    printf("Checking linked list as a stack\n");

    char* Strings[] = { "Wake", "up", "Neo", "Matrix", "has", "you" };
    bakge::LinkedList<char*> List;
    
    /* Push values to list */
    for (int i = 0; i < sizeof(Strings) / sizeof(char*); i++) {
        List.Push(Strings[i]);
    }

    /* Pop values in reversed order */
    while (!List.IsEmpty()) {
        char* Popped = List.Pop();
        printf("%s ", Popped);
    }
    printf("\n");

    /* Try to pop from empty list */
    try {
        char* Popped = List.Pop();
        printf ("Something is wrong");
    } catch (char* Exception) {
        printf ("Exception successfully thrown: %s\n", Exception);
    }

    return 0;
}

